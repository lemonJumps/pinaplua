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
    
    xor r10, r10

    dec r9d
    jz __winCall
    cmp qword ptr [r8 + r10], 1
    je _rcxSW1
    cmp qword ptr [r8 + r10], 2
    je _rcxSW2
    cmp qword ptr [r8 + r10], 4
    je _rcxSW4
    cmp qword ptr [r8 + r10], 8
    je _rcxSW8
    
_rcxSW1:
    mov r11b, byte ptr [rdx + r10]
    jmp _rcxSWend
_rcxSW2:
    mov r11w, word ptr [rdx + r10]
    jmp _rcxSWend
_rcxSW4:
    mov r11d, dword ptr [rdx + r10]
    jmp _rcxSWend
_rcxSW8:
    mov r11, qword ptr [rdx + r10]
    jmp _rcxSWend
_rcxSWend:
    inc r10

    dec r9d
    jz __winCall
    cmp qword ptr [r8 + r10], 1
    je _rdxSW1
    cmp qword ptr [r8 + r10], 2
    je _rdxSW2
    cmp qword ptr [r8 + r10], 4
    je _rdxSW4
    cmp qword ptr [r8 + r10], 8
    je _rdxSW8
    
_rdxSW1:
    mov r12b, byte ptr [rdx + r10]
    jmp _rdxSWend
_rdxSW2:
    mov r12w, word ptr [rdx + r10]
    jmp _rdxSWend
_rdxSW4:
    mov r12d, dword ptr [rdx + r10]
    jmp _rdxSWend
_rdxSW8:
    mov r12, qword ptr [rdx + r10]
    jmp _rdxSWend
_rdxSWend:
    inc r10

    dec r9d
    jz __winCall
    cmp qword ptr [r8 + r10], 1
    je _r8SW1
    cmp qword ptr [r8 + r10], 2
    je _r8SW2
    cmp qword ptr [r8 + r10], 4
    je _r8SW4
    cmp qword ptr [r8 + r10], 8
    je _r8SW8
    
_r8SW1:
    mov r13b, byte ptr [r8 + r10]
    jmp _r8SWend
_r8SW2:
    mov r13w, word ptr [r8 + r10]
    jmp _r8SWend
_r8SW4:
    mov r13d, dword ptr [r8 + r10]
    jmp _r8SWend
_r8SW8:
    mov r13, qword ptr [r8 + r10]
    jmp _r8SWend
_r8SWend:
    inc r10

    dec r9d
    jz __winCall
    cmp qword ptr [r8 + r10], 1
    je _r9SW1
    cmp qword ptr [r8 + r10], 2
    je _r9SW2
    cmp qword ptr [r8 + r10], 4
    je _r9SW4
    cmp qword ptr [r8 + r10], 8
    je _r9SW8
    
_r9SW1:
    mov r14b, byte ptr [r8 + r10]
    jmp _r9SWend
_r9SW2:
    mov r14w, word ptr [r8 + r10]
    jmp _r9SWend
_r9SW4:
    mov r14d, dword ptr [r8 + r10]
    jmp _r9SWend
_r9SW8:
    mov r14, qword ptr [r8 + r10]
    jmp _r9SWend
_r9SWend:
    inc r10

__winCallLoop:
    dec r9d
    nop
    jnz __winCallLoop
__winCall:
    call rcx
    pop rbp
    ret

