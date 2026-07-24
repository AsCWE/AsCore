#include "uart.h"
#include <stdint.h>
#define UART_THR ((volatile char*)0x10000000)
#define UART_LSR ((volatile char*)0x10000005)

void uart_putc(char c){

   // while((*UART_LSR & 0X20) == 0){

        *UART_THR = c;

    //}
}
void uart_print(const char *str){

    for(; *str != '\0'; str++){

        uart_putc(*str);
    }

}
void uart_printhex(uint32_t val){

    uart_print("0x");

    for(int i = 7; i >= 0; i--){
        uint8_t nibble = (val >> (i * 4)) & 0xF;
        if(nibble < 10){
            uart_putc('0'+ nibble);
        }
        else{
            uart_putc('A' + (nibble - 10));
        }
    }

}
