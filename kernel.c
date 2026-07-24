#include "uart.h"
#include <stdint.h>
#include "shell.h"
#include "task.h"
#include "ipc.h"

extern volatile int cmd_ready;
extern volatile int cmd_idx;
extern char cmd_buffer[];
extern void read_command(char *cmd);


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

    task_init();
    current_task = task_create(PID_SHELL, "shell");
    current_task->state = TASK_RUNNING;

    task_create(PID_ENCRYPT_NET, "encrypt_net");

    uart_print("AsCore Kernel Booted Successfully!\n");

    print_banner();
    print_prompt();

    while(1){
        if(cmd_ready){
            read_command(cmd_buffer);
            cmd_idx = 0;
            cmd_ready = 0;
            print_prompt();
        }
    }
}
