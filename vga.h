#ifndef VGA_H
#define VGA_H

#define VGA_COLOR_GREEN 0x0A
#define VGA_COLOR_RED 0x0C
#define VGA_COLOR_WHITE 0X0F

void clear_screen(void);
void print(char *str);
void update_cursor(int x, int y);

#endif
