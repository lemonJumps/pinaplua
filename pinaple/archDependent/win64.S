# x86-64 MICROSOFT (ew) version

.intel_syntax noprefix
.global pinADcallCDECL32

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
    dec r9d
    jz __winCall
    cmp

__winCallLoop:
    dec r9d
    push 
    jnz __cdecl32Loop
__winCall:
    call rcx
    pop rbp
    ret

