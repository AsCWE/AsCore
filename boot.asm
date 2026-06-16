[BITS 16]
[ORG 0x7C00]
start:
xor ax,ax 
mov ds,ax

mov si, TEXT
call PrintString

jmp $


PrintChar:
mov ah, 0x0E
mov bh, 0x00
mov bl, 0x07

INT 0x10
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


TEXT db 'AsCore 0.0.1 booting...', 0

times 510 - ($ - $$) db 0
dw 0xAA55
