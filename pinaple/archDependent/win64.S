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
    mov rbp, rsp
    
    xor r15, r15
    xor r10, r10

    dec r9d
    jz __winCall

    mov rax, qword ptr [r8 + r10]
    cmp rax, 1
    je _rcxSWfloat
    cmp rax, 2
    je _rcxSWdouble
    mov r11, qword ptr [rdx + r10]
    jmp _rcxSWend
_rcxSWfloat:
    movss xmm0, dword ptr [rdx + r10]
    jmp _rcxSWend
_rcxSWdouble:
    movsd xmm0, qword ptr [rdx + r10]
_rcxSWend:
    add r10, 8

    dec r9d
    jz __winCall

    mov rax, qword ptr [r8 + r10]
    cmp rax, 1
    je _rdxSWfloat
    cmp rax, 2
    je _rdxSWdouble
    mov r12, qword ptr [rdx + r10]
    jmp _rdxSWend
_rdxSWfloat:
    movss xmm1, dword ptr [rdx + r10]
    jmp _rdxSWend
_rdxSWdouble:
    movsd xmm1, qword ptr [rdx + r10]
_rdxSWend:
    add r10, 8

    dec r9d
    jz __winCall

    mov rax, qword ptr [r8 + r10]
    cmp rax, 1
    je _r8SWfloat
    cmp rax, 2
    je _r8SWdouble
    mov r13, qword ptr [rdx + r10]
    jmp _r8SWend
_r8SWfloat:
    movss xmm2, dword ptr [rdx + r10]
    jmp _r8SWend
_r8SWdouble:
    movsd xmm2, qword ptr [rdx + r10]
_r8SWend:
    add r10, 8

    dec r9d
    jz __winCall

    mov rax, qword ptr [r8 + r10]
    cmp rax, 1
    je _r9SWfloat
    cmp rax, 2
    je _r9SWdouble
    mov r14, qword ptr [rdx + r10]
    jmp _r9SWend
_r9SWfloat:
    movss xmm3, dword ptr [rdx + r10]
    jmp _r9SWend
_r9SWdouble:
    movsd xmm3, qword ptr [rdx + r10]
_r9SWend:
    add r10, 8

    cmp r9d, 0
    je __winCall

__winCallLoop:
    push qword ptr [rdx + r10]
    add r15, 8
    add r10, 8
    dec r9d
    jnz __winCallLoop
__winCall:
    mov rax, rcx
    mov rcx, r11
    mov rdx, r12
    mov r8, r13
    mov r9, r14

    mov qword ptr [rbp + 16], r15

    sub rsp, 32

    call rax

    mov r15, qword ptr [rbp + 16]
    add rsp, r15
    add rsp, 32
    
    pop rbp
    ret

