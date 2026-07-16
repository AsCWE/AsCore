#include "uart.h"
#include<stdint.h>

void kernel_main(void){

    uart_print("AsCore Kernel Booted Successfully!\n");
    *(volatile uint8_t *)(0x10000000 + 1) = 0x01;
    *(volatile uint32_t *)(0x0C000000 + (10 * 4)) = 1;
    *(volatile uint32_t *)(0x0C002000) = (1 << 10);
    *(volatile uint32_t *)(0x0C200000) = 0;
    asm volatile("csrs mie, %0" :: "r"(1 << 11));
    asm volatile("csrs mstatus, %0" :: "r"(1 << 3));
    uart_print("AsCore: waiting for Keyboard Interrupt.\n");
    asm volatile("ecall");

    while(1){

    }
}
