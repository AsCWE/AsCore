#include <stdint.h>
#include "uart.h"
#include "shell.h"
#include "ipc.h"

extern void uart_print(const char *str);

void trap_handler(uint32_t arg0, uint32_t arg1, uint32_t arg2){
    uint32_t mcause;
    uint32_t mepc;

    asm volatile("csrr %0, mepc" : "=r"(mepc));
    asm volatile("csrr %0, mcause" : "=r"(mcause));

    if ((mcause >> 31) == 1) {
        uint32_t int_id = mcause & 0x7FFFFFFF;

        if (int_id == 7) {
            uart_print("[Debug]: Timer interrupt received.\n");
        }
        else if (int_id == 11){
            volatile uint32_t *plic_claim =(volatile uint32_t *)0x0C200004;
            uint32_t irq = *plic_claim;
            if(irq == 10){
                volatile uint8_t *uart_thr = (volatile uint8_t *)(0x10000000);
                char c = *uart_thr;

                shell_inputc(c);

            }
            *plic_claim = irq;
        }
        else{
            uart_print("[Debug]: Unknown external hardware interrupt received.\n");
        }
    }
    else {
        uint32_t exc_id = mcause & 0x7FFFFFFF;

        if(exc_id == 11 || exc_id == 8 || exc_id == 9 || exc_id == 10){
            uart_print("[Debug]: Syscall (ecall) received!\n");
            uint32_t res = ipc_handler(arg0, arg1, arg2);
            asm volatile ("mv a0, %0" :: "r"(res));
            mepc += 4;
            asm volatile("csrw mepc, %0" :: "r"(mepc));
        }
        else {
            uart_print("[Debug]: Kernel Panic !\n");
            while(1);
        }
    }
}
