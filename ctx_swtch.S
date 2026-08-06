.section .text
.global ctx_swtch
.global task_trampoline


ctx_swtch:
 csrrci t0, mstatus, 0x8
 addi sp, sp, -56

 sw ra, 0(sp)
 sw s0, 4(sp)
 sw s1, 8(sp)
 sw s2, 12(sp)
 sw s3, 16(sp)
 sw s4, 20(sp)
 sw s5, 24(sp)
 sw s6, 28(sp)
 sw s7, 32(sp)
 sw s8, 36(sp)
 sw s9, 40(sp)
 sw s10, 44(sp)
 sw s11, 48(sp)

 sw sp, 0(a0)
 mv sp, a1

 lw ra,  0(sp)
 lw s0,  4(sp)
 lw s1,  8(sp)
 lw s2, 12(sp)
 lw s3, 16(sp)
 lw s4, 20(sp)
 lw s5, 24(sp)
 lw s6, 28(sp)
 lw s7, 32(sp)
 lw s8, 36(sp)
 lw s9, 40(sp)
 lw s10,44(sp)
 lw s11,48(sp)
 csrw mstatus, t0
 addi sp, sp, 56
ret
