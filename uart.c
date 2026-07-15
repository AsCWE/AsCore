#include "uart.h"
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
