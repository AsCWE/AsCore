__asm__(".code16gcc\n");

volatile char* video_mem = (char*)0xB8000;
int cursor_x = 0;
int cursor_y = 0;

void kernel_main(){

for (int i = 0; i < 80 * 25; i++) {
  video_mem[i * 2] = ' ';
  video_mem[i * 2 + 1] = 0x0A;
}

void print(char *str);

print("Welcome to AsCore!\n");

while(1){
__asm__ volatile("hlt");
}
}

void print(char *str){

for(; *str != '\0'; str++){

if(*str == '\n'){
cursor_x = 0;
cursor_y++;
}
else{

int offset = (cursor_y * 80 + cursor_x) * 2;
video_mem[offset] = *str;
video_mem[offset + 1] = 0x0A;
cursor_x++;
}
}
}
