__asm__(".code16gcc\n");

#include "vga.h"
#include "io.h"
#include <stdint.h>

static char current_color = VGA_COLOR_WHITE;

static volatile char* video_mem = (char*)0xB8000;
static int cursor_x = 0;
static int cursor_y = 0;

void clear_screen(void){

 for(int i = 0; i < 80 * 25; i++){

    video_mem[i * 2] = ' ';
    video_mem[i * 2 + 1] = current_color;
  }
}

void update_cursor(int x, int y){
    uint16_t position = (y * 80) + x;

    outb(0x3D4, 14);
    outb(0x3D5,(position >> 8) & 0xFF);
    outb(0x3D4, 15);
    outb(0x3D5, position & 0xFF);

}
void print(char *str){

 for(; *str != '\0'; str++){

  if(*str == '\n'){
    cursor_x = 0;
    cursor_y++;
}
  else {
    int offset = (cursor_y * 80 + cursor_x) * 2;
    video_mem[offset] = *str;
    video_mem[offset + 1] = current_color;
    cursor_x++;
    }
  }
}

