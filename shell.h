#ifndef SHELL_H
#define SHELL_H

extern volatile int cmd_ready;
extern volatile int cmd_idx;


void print_banner(void);
void print_prompt(void);
void shell_inputc(char c);

#endif
