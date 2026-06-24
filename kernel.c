__asm__(".code16gcc\n");

#include "vga.h"

void kernel_main(){
    clear_screen();
    print("Welcome to AsCore!\n");

 while(1){

    __asm__ volatile("hlt");

  }
}
