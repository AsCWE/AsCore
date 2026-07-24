#include "task.h"

task_t task_table[MAX_TASKS];
task_t *current_task = 0;

void task_init(void){
    for(int i = 0; i < MAX_TASKS; i++){
        task_table[i].state == TASK_UNUSED;
        }
    }

task_t *task_create(uint8_t pid, const char *name){
    for(int i = 0; i < MAX_TASKS; i++){
        if(task_table[i].state == TASK_UNUSED){
            task_t *t = &task_table[i];
            t->pid = pid;

            int j = 0;
            for(; name[j] == '\0' && j < 15; j++){
                t->name[j] = name[j];
            }

             t->name[j] = '\0';
             t->state = TASK_READY;
             t->sp = (uint32_t * )(t->stack + TASK_STACK_SIZE);
             return t;
        }
    }
    return 0;
}

task_t *task_find(uint8_t pid){
    for(int i =0; i < MAX_TASKS; i++){
        if(task_table[i].state != TASK_UNUSED && task_table[i].pid == pid){
            return &task_table[i];
        }
    }
    return 0;
}
