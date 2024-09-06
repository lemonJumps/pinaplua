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

    xor r15, r15

    cmp r9d, 0
    je __winCall

    mov rax, qword ptr [r8 + 0]
    cmp rax, 1
    je _rcxSWfloat
    cmp rax, 2
    je _rcxSWdouble
    mov r11, qword ptr [rdx + 0]
    jmp _rcxSWend
_rcxSWfloat:
    movss xmm0, dword ptr [rdx + 0]
    jmp _rcxSWend
_rcxSWdouble:
    movsd xmm0, qword ptr [rdx + 0]
_rcxSWend:

    dec r9d
    jz __winCall

    mov rax, qword ptr [r8 + 8]
    cmp rax, 1
    je _rdxSWfloat
    cmp rax, 2
    je _rdxSWdouble
    mov r12, qword ptr [rdx + 8]
    jmp _rdxSWend
_rdxSWfloat:
    movss xmm1, dword ptr [rdx + 8]
    jmp _rdxSWend
_rdxSWdouble:
    movsd xmm1, qword ptr [rdx + 8]
_rdxSWend:

    dec r9d
    jz __winCall

    mov rax, qword ptr [r8 + 16]
    cmp rax, 1
    je _r8SWfloat
    cmp rax, 2
    je _r8SWdouble
    mov r13, qword ptr [rdx + 16]
    jmp _r8SWend
_r8SWfloat:
    movss xmm2, dword ptr [rdx + 16]
    jmp _r8SWend
_r8SWdouble:
    movsd xmm2, qword ptr [rdx + 16]
_r8SWend:

    dec r9d
    jz __winCall

    mov rax, qword ptr [r8 + 24]
    cmp rax, 1
    je _r9SWfloat
    cmp rax, 2
    je _r9SWdouble
    mov r14, qword ptr [rdx + 24]
    jmp _r9SWend
_r9SWfloat:
    movss xmm3, dword ptr [rdx + 24]
    jmp _r9SWend
_r9SWdouble:
    movsd xmm3, qword ptr [rdx + 24]
_r9SWend:

    dec r9d
    jz __winCall

    add rdx, 24
    imul r9, 8

__winCallLoop:
    push qword ptr [rdx + r9]
    add r15, 8
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

