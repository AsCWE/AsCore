#include "encrypt_net.h"
#include "ipc.h"
#include "uart.h"
#include "task.h"

extern uint32_t test_ipc_call(uint32_t cmd, uint32_t target, uint32_t data);

void encrypt_net_main(void){
    for(;;){
        uint32_t status = test_ipc_call(IPC_RECV, 0, 0);
        if(status != 0x00000006 && status != 0x00000007){
            uart_print("[encrypt_net]: Message: ");
            uart_printhex(status);
            uart_print("\n");
        }
     yield();

    }
}
