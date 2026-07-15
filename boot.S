.section .text.init
.global _start
.extern trap_vector

_start:
    la sp, stack_top
    la t0, trap_vector
    csrw mtvec, t0
    jal ra, kernel_main

.hang:
    wfi
    j .hang
