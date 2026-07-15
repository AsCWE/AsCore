#include "uart.h"
#include<stdint.h>

void kernel_main(void){

    uart_print("AsCore Kernel Booted Successfully!\n");
    *(volatile uint8_t *)(0x10000000 + 1) =0x10;
    asm volatile("csrs mie, %0" :: "r"(1 << 11));
    asm volatile("csrs mstatus, %0" :: "r"(1 << 3));
    uart_print("AsCore: waiting for Keyboard Interrupt.\n");
    asm volatile("ecall");

    while(1){

    }
}
