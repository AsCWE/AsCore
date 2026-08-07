#ifndef IPC_H
#define IPC_H
#include<stdint.h>

#define PID_SHELL  ((uint8_t)1)
#define PID_DRIVER ((uint8_t)2)
#define PID_ENCRYPT_NET ((uint8_t)3)

#define IPC_SEND 0x01
#define IPC_RECV 0x02

typedef struct {
    uint8_t sender_pid;
    uint32_t target_pid;
} ipc_permission_t;

int ipc_permission_check(uint8_t sender_pid, uint8_t target_pid);

uint32_t ipc_handler(uint32_t command_type, uint32_t target_pid, uint32_t payload);

#endif

