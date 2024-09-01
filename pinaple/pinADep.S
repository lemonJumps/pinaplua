# x86-64 version

.intel_syntax noprefix
.global pinADcallCDECL32

pinADcallCDECL32:
    push rbp
    mov rbp, rsp
    mov qword ptr [rbp + 0x10], rcx
    mov qword ptr [rbp + 0x18], rcx
    mov qword ptr [rbp + 0x20], rcx
    mov qword ptr [rbp + 0x28], rcx

    pop rbp
    ret

