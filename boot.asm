[BITS 16]
[ORG 0x7C00]

start:

 xor ax,ax
 mov ds,ax

 mov si, welcome
 call PrintString

 mov bx, 0x8000
 call ReadDisk
 mov si, dsuccess
 call PrintString
 jmp $

ReadDisk:

 mov ah, 0x02
 mov al, 1
 mov ch, 0
 mov cl, 2
 mov dh, 0
 mov dl, 0x00
 int 0x13
 jc DiskError
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

NextChar:
 mov al, [si]
 inc si
 or al,al
 jz exit
 call PrintChar
 jmp NextChar

exit:
 ret


welcome db 'Welcome to AsCore!',13 ,10 ,0
derror db 'Failed to read from sector',13 ,10 ,0
dsuccess db 'Reading sector 2 success',13, 10 ,0
times 510 - ($ - $$) db 0
dw 0xAA55

times 512 db 0xDE
