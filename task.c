#include "task.h"
#include "uart.h"

task_t task_table[MAX_TASKS];
task_t *current_task = 0;

extern void ctx_swtch(uint32_t **old_sp, uint32_t *new_sp);
void task_trampoline(void);

void task_init(void){
    for(int i = 0; i < MAX_TASKS; i++){
        task_table[i].state = TASK_UNUSED;
    }
}

static task_t *task_alloc(uint8_t pid, const char *name){
    for(int i = 0; i < MAX_TASKS; i++){
        if(task_table[i].state == TASK_UNUSED){
            task_t *t = &task_table[i];
            t->pid = pid;

            int j = 0;
            for(; name[j] != '\0' && j < 15; j++) t->name[j] = name[j];
            t->name[j] = '\0';

            t->mbox_head = 0;
            t->mbox_tail = 0;
            t->mbox_count = 0;
            t->entry = 0;
            return t;
        }
    }
    return 0;
}


task_t *task_create(uint8_t pid, const char *name){
    task_t *t = task_alloc(pid, name);
    if(!t) return 0;
    t->state = TASK_READY;
    t->sp = (uint32_t *)(t->stack + TASK_STACK_SIZE);
    return t;
}


task_t *task_spawn(uint8_t pid, const char *name, task_entry_t entry){
    task_t *t = task_alloc(pid, name);
    if(!t) return 0;

    t->entry = entry;

    uint32_t *sp = (uint32_t *)(t->stack + TASK_STACK_SIZE);
    sp -= 14;
    sp[0] = (uint32_t)task_trampoline;
    for(int i = 1; i < 13; i++) sp[i] = 0;
    sp[13] = (1 << 3);

    t->sp = sp;
    t->state = TASK_READY;
    return t;
}

void task_trampoline(void){
    current_task->entry();
    current_task->state = TASK_UNUSED;
    while(1){
        yield();
    }
}

task_t *task_find(uint8_t pid){
    for(int i = 0; i < MAX_TASKS; i++){
        if(task_table[i].state != TASK_UNUSED && task_table[i].pid == pid){
            return &task_table[i];
        }
    }
    return 0;
}

int mailbox_push(task_t *target, uint8_t sender_pid, uint32_t payload){
    if(target->mbox_count >= MAILBOX_SIZE){
        return 0;
    }
    target->mailbox[target->mbox_tail].sender_pid = sender_pid;
    target->mailbox[target->mbox_tail].payload = payload;
    target->mbox_tail = (target->mbox_tail + 1) % MAILBOX_SIZE;
    target->mbox_count++;
    if(target->state == TASK_BLOCKED){
        target->state = TASK_READY;
    }
    return 1;
}

int mailbox_pop(task_t *owner, message_t *out){
    if(owner->mbox_count == 0){
        return 0;
    }
    *out = owner->mailbox[owner->mbox_head];
    owner->mbox_head = (owner->mbox_head + 1) % MAILBOX_SIZE;
    owner->mbox_count--;
    return 1;
}

static task_t *schedule_next(void){
    if(!current_task) return 0;
    int start = (int)(current_task - task_table);
    for(int i = 1; i <= MAX_TASKS; i++){
        int idx = (start + i) % MAX_TASKS;
        task_state_t s = task_table[idx].state;
        if(s == TASK_READY || s == TASK_RUNNING){
            return &task_table[idx];
        }
    }
    return current_task;
}

void yield(void){
    task_t *prev = current_task;
    task_t *next = schedule_next();

    if(!next || next == prev) return;

    if(prev->state == TASK_RUNNING) prev->state = TASK_READY;
    next->state = TASK_RUNNING;
    current_task = next;

    ctx_swtch(&prev->sp, next->sp);
}
