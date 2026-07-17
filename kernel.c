#include "uart.h"
#include <stdint.h>
#include "shell.h"

static inline void init_hardware(void){

    *(volatile uint8_t *)(0x10000000 + 1) = 0x01;
    *(volatile uint32_t *)(0x0C000000 + (10 * 4)) = 1;
    *(volatile uint32_t *)(0x0C002000) = (1 << 10);
    *(volatile uint32_t *)(0x0C200000) = 0;
    asm volatile("csrs mie, %0" :: "r"(1 << 11));
    asm volatile("csrs mstatus, %0" :: "r"(1 << 3));
}


void kernel_main(void){
    init_hardware();
    uart_print("AsCore Kernel Booted Successfully!\n");
    print_banner();
    print_prompt();

    while(1){

    }
}
