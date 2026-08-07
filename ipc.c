#include "ipc.h"
#include "uart.h"
#include "task.h"

extern void uart_print(const char *str);
extern void uart_putc(char c);
extern void uart_printhex(uint32_t val);

static const ipc_permission_t ipc_permissions[] = {
    { PID_SHELL, PID_ENCRYPT_NET },
};

#define IPC_PERMISSION_COUNT (sizeof(ipc_permissions) / sizeof(ipc_permissions[0]))

int ipc_permission_check(uint8_t sender_pid, uint8_t target_pid){
    for(uint32_t i = 0; i < IPC_PERMISSION_COUNT; i++){
        if(ipc_permissions[i].sender_pid == sender_pid && ipc_permissions[i].target_pid == target_pid){
            return 1;
        }
    }
}

uint32_t ipc_handler(uint32_t command_type, uint32_t target_pid, uint32_t payload){

uint8_t sender_pid = current_task ? current_task->pid : 0;

    switch(command_type){

        case IPC_SEND: {

            if(target_pid > 255){
                uart_print("[IPC]: Invalid target PID (out of range)!\n");
                return 0x00000003;
            }

           task_t *target = task_find((uint8_t)target_pid);

           if(target == 0){
           uart_print("[IPC]: Target process does not exist!\n");
           return 0x00000004;
           }


           if(sender_pid == PID_SHELL && target_pid == PID_ENCRYPT_NET){

               if(!mailbox_push(target, sender_pid, payload)){
                   uart_print("[IPC]: Mailbox full, message dropped!\n");
                   return 0x00000005;
               }



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
        case IPC_RECV: {

            message_t msg;

            if(!current_task){
                return 0x00000006;
            }

            if(!mailbox_pop(current_task, &msg)){
                current_task->state = TASK_BLOCKED;
                return 0x00000007;

            }

            uart_print("[IPC]: Received from: ");
            uart_printhex(msg.sender_pid);
            uart_print(" | Data: ");
            uart_printhex(msg.payload);
            uart_print("\n");
            return msg.payload;
        }
    }
    return 0x00000002;
}
