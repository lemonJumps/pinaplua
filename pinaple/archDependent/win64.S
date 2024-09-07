# x86-64 MICROSOFT (ew) version

.intel_syntax noprefix
.global pinADcallWIN

# x64 windows calling convention
# RCX, RDX, R8, R9 for integer 
# XMM0, XMM1, XMM2, XMM3 for float
# returns RAX when 64bit
# returns XMM0 when float

# for our call:
# r9d contains argument count
# r8 contains array of sizes
# rdx contains array of values
# rcx contains function pointer



pinADcallWIN:
    push rbp
    push r11 
    push r12 
    push r13
    push r14
    push r15
    mov rbp, rsp

    cmp r9, 1
    je _winCall1
    cmp r9, 2
    je _winCall2
    cmp r9, 3
    je _winCall3
    
    jmp _winCall4p

_winCall1:
    mov rsp, rdx

    movsd xmm0, qword ptr [rsp]
    pop r11

    mov rsp, rbp
    jmp __winCall

_winCall2:
    mov rsp, rdx

    movsd xmm0, qword ptr [rsp]
    pop r11
    movsd xmm1, qword ptr [rsp]
    pop r12

    mov rsp, rbp
    jmp __winCall

_winCall3:
    mov rsp, rdx

    movsd xmm0, qword ptr [rsp]
    pop r11
    movsd xmm1, qword ptr [rsp]
    pop r12
    movsd xmm2, qword ptr [rsp]
    pop r13

    mov rsp, rbp
    jmp __winCall

_winCall4p:
    mov rsp, rdx

    movsd xmm0, qword ptr [rsp]
    pop r11
    movsd xmm1, qword ptr [rsp]
    pop r12
    movsd xmm2, qword ptr [rsp]
    pop r13
    movsd xmm3, qword ptr [rsp]
    pop r14

    mov rsp, rbp

    sub r9d, 4
    jz __winCall

    add rdx, 24
    imul r9, 8
    mov r15, r9

__winCallLoop:
    push qword ptr [rdx + r9]
    sub r9d, 8
    jnz __winCallLoop

__winCall:
    mov rax, rcx
    mov rcx, r11
    mov rdx, r12
    mov r8, r13
    mov r9, r14

    sub rsp, 32

    call rax

    add rsp, r15
    add rsp, 32

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop rbp
    ret

