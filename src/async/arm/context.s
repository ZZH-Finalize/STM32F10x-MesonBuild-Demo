.thumb
.align 4
.section .text.PendSV_Handler
.global PendSV_Handler
.type PendSV_Handler, %function

PendSV_Handler:
    nop
    nop
    nop
    bkpt

.section .text.SVC_Handler
.global SVC_Handler
.type SVC_Handler, %function

SVC_Handler:
    nop
    nop
    nop
    bkpt
