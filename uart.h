#include <stdint.h>
#ifndef UART_H
#define UART_H

void uart_print(const char *str);
void uart_putc(char c);
void uart_printhex(uint32_t val);

#endif
