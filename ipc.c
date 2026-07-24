#include "ipc.h"
#include "uart.h"
#include "task.h"

extern void uart_print(const char *str);
extern void uart_putc(char c);
extern void uart_printhex(uint32_t val);

uint32_t ipc_handler(uint32_t command_type, uint32_t target_pid, uint32_t payload){

uint8_t sender_pid = current_task ? current_task->pid : 0;

    switch(command_type){

        case IPC_SEND:
            if(sender_pid == PID_SHELL && target_pid == PID_ENCRYPT_NET){
                uart_print("[IPC]: Secure Send! Sender: ");
                uart_printhex(sender_pid);

                uart_print(" -> Target: ");
                uart_printhex(target_pid);

                uart_print(" | Data: ");
                uart_printhex(payload);
                uart_print("\n");
                return 0x00000000;
            }

           else {
               uart_print("\n [IPC]: Unauthorized IPC attempt !\n");
               return 0x00000001;
        }
    }
    return 0x00000002;
}
