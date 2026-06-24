[BITS 16]
[EXTERN kernel_main]

global _start

_start:
 call kernel_main
 jmp $
