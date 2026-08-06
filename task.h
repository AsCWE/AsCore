#ifndef TASK_H
#define TASK_H

#include <stdint.h>

#define MAX_TASKS 8
#define TASK_STACK_SIZE 2048
#define MAILBOX_SIZE 4

typedef enum {
    TASK_UNUSED = 0,
    TASK_READY,
    TASK_RUNNING,
    TASK_BLOCKED
} task_state_t;

typedef struct {
    uint8_t  sender_pid;
    uint32_t payload;
} message_t;

typedef void (*task_entry_t)(void);

typedef struct {
    uint32_t ra, gp, tp;
    uint32_t t0, t1, t2;
    uint32_t s0, s1;
    uint32_t a0, a1, a2, a3, a4, a5, a6, a7;
    uint32_t s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
    uint32_t t3, t4, t5, t6;
    uint32_t mepc;
    uint32_t mstatus;
} task_context_t;

typedef struct {
    uint8_t pid;
    char name[16];
    task_state_t state;
    task_context_t ctx;
    uint32_t *sp;
    uint8_t stack[TASK_STACK_SIZE];
    task_entry_t entry;

    message_t mailbox[MAILBOX_SIZE];
    uint8_t mbox_head;
    uint8_t mbox_tail;
    uint8_t mbox_count;
} task_t;

extern task_t task_table[MAX_TASKS];
extern task_t *current_task;

void task_init(void);
task_t *task_create(uint8_t pid, const char *name);
task_t *task_spawn(uint8_t pid, const char *name, task_entry_t entry);
task_t *task_find(uint8_t pid);

int mailbox_push(task_t *target, uint8_t sender_pid, uint32_t payload);
int mailbox_pop(task_t *owner, message_t *out);

void yield(void);

#endif
