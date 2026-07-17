#include "uart.h"
#include "shell.h"
#include <stdint.h>

#define CMD_LEN_MAX 64

char cmd_buffer[CMD_LEN_MAX];
int cmd_idx = 0;

#define PRINT_RESET   "\033[0m"
#define PRINT_BOLD    "\033[1m"
#define PRINT_CYAN    "\033[36m"
#define PRINT_GREEN   "\033[32m"
#define PRINT_RED     "\033[31m"
#define PRINT_CLEAR   "\033[H\033[J"

void print_banner(void){

    uart_print(PRINT_CLEAR);
    uart_print(PRINT_CYAN PRINT_BOLD);
    uart_print("========================================================\n");
    uart_print("    ###     ######   ######   #######  ########  ######\n");
    uart_print("   ## ##   ##    ## ##    ## ##     ## ##     ## ##\n");
    uart_print("  ##   ##  ##       ##       ##     ## ##     ## ##\n");
    uart_print(" ##     ##  ######  ##       ##     ## ########  ######\n");
    uart_print(" #########       ## ##       ##     ## ##   ##   ##\n");
    uart_print(" ##     ## ##    ## ##    ## ##     ## ##    ##  ##\n");
    uart_print(" ##     ##  ######   ######   #######  ##     ## ######\n");
    uart_print("========================================================\n" PRINT_RESET);
    uart_print(PRINT_CYAN "AsCore v0.0.2(RV32I-ML-15/07/2026)\n" PRINT_RESET);
    uart_print("Type \"help\" to see available commands.\n\n ");
}
void print_prompt(void){

    uart_print(PRINT_GREEN PRINT_BOLD "[AsCore] # " PRINT_RESET);
}


void read_command(char* cmd){
    uart_print("\n");
    if(cmd_idx == 0){
        return;
    }

 int help = (cmd[0] == 'h' && cmd[1] == 'e' && cmd[2] == 'l' && cmd[3] == 'p' && cmd[4] == '\0');
 int clear = (cmd[0] == 'c' && cmd[1] == 'l' && cmd[2] == 'e' && cmd[3] == 'a' && cmd[4] == 'r' && cmd[5] == '\0');
 int about = (cmd[0] == 'a' && cmd[1] == 'b' && cmd[2] == 'o' && cmd[3] == 'u' && cmd[4] == 't' && cmd[5] == '\0');


    if(help){
        uart_print(PRINT_BOLD "Available Commands: \n" PRINT_RESET);
        uart_print(" help - Show this help menu.\n");
        uart_print(" clear - Clear the screen.\n");
        uart_print(" about - Learn more about AsCore.\n");
    }

    else if(about){
        uart_print("AsCore is a hobbyist operating system built from the ground up.\n");
        uart_print("Architecture: RISC-V (RV32I).\n");
        uart_print("Author: AsCWE(Self-Taught Systems Programmer) from Turkey.\n");
    }

    else if(clear){
     print_banner();
    }

    else{
        uart_print(PRINT_RED "Unknown command.\n" PRINT_RESET);
    }

}

void shell_inputc(char c){

    if(c == '\r' || c == '\n'){

        cmd_buffer[cmd_idx] = '\0';
        read_command(cmd_buffer);
        cmd_idx = 0;
        print_prompt();
    }

    else if(c == 127 || c == '\b'){
        if(cmd_idx > 0){
            cmd_idx--;
            uart_print("\b \b");
        }

    }
    else{
        if(cmd_idx < CMD_LEN_MAX - 1){
            cmd_buffer[cmd_idx++] = c;
            uart_putc(c);
        }
    }
}
