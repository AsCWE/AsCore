__asm__(".code16gcc\n");

void kernel_main(){

volatile char* video_mem = (char*)0xB8000;

for (int i = 0; i < 80 * 25; i++) {
  video_mem[i * 2] = ' ';
  video_mem[i * 2 + 1] = 0x07;
}

video_mem[0] = 'A';
video_mem[1] = 0x02;

while(1){

__asm__ volatile("hlt");

}
}
