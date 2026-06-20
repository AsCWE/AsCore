[BITS 16]
[ORG 0x7C00]

start:

 xor ax,ax
 mov ds,ax
 mov es,ax
 mov ss,ax
 mov sp, 0x7E00

 mov si, welcome
 call PrintString

 mov bx, 0x7E00
 call ReadDisk

 mov si, dsuccess
 call PrintString

 jmp 0x0000:0x7E00

ReadDisk:

 pusha

 mov ah, 0x02
 mov al, 15
 mov ch, 0
 mov cl, 2
 mov dh, 0
 mov dl, 0x00
 int 0x13
 jc DiskError
 popa
 ret

DiskError:
 mov si, derror
 call PrintString

PrintChar:

 mov ah, 0x0E
 mov bh, 0x00
 mov bl, 0x07
 int 0x10
 ret



PrintString:
 mov ah, 0x0E
.loop:
 lodsb
 cmp al, 0
 je .done
 int 0x10
 jmp .loop
.done:
 ret


welcome db 'Welcome to AsCore!',13 ,10 ,0
derror db 'Failed to read from sector',13 ,10 ,0
dsuccess db 'Reading sector success',13, 10 ,0

times 510 - ($ - $$) db 0
dw 0xAA55
