#include <stdint.h>
#include "uart.h"
#include "shell.h"

extern void uart_print(const char *str);

void trap_handler(void){
    uint32_t mcause;
    uint32_t mepc;

    asm volatile("csrr %0, mepc" : "=r"(mepc));
    asm volatile("csrr %0, mcause" : "=r"(mcause));

    if ((mcause >> 31) == 1) {
        uint32_t int_id = mcause & 0x7FFFFFFF;

        if (int_id == 7) {
            uart_print("AsCore: Timer interrupt received.\n");
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
            uart_print("AsCore: Unknown external hardware interrupt received.\n");
        }
    }
    else {
        uint32_t exc_id = mcause & 0x7FFFFFFF;

        if (exc_id == 11) {
            uart_print("AsCore: Syscall (ecall) received!\n");
            mepc += 4;
            asm volatile("csrw mepc, %0" :: "r"(mepc));
        }
        else {
            uart_print("AsCore: Kernel Panic !\n");
            while(1);
        }
    }
}
