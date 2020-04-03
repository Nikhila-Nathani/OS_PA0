
.globl zfunction
zfunction:
    PUSH %EBP
    MOV %ESP,%EBP
    SUB 0x10,%ESP;
    MOVL 0x8(%EBP),%EAX
    ANDL $0xff803fff,%EAX
    SAL $4,%EAX
    MOVL %EAX,%EBP
    POP %EBP
    RET
