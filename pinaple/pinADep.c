/**
 * @file pinADep.c
 * @author Lemon Jumps (you@domain.com)
 * @brief architecture deoendent code
 * @version 0.1
 * @date 2024-08-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "pinADep.h"


#ifdef __PIN_ARCH_AMD64__

// __attribute__ ((naked)) void pinADcallCDECL32(void * function, void * values, size_t * sizes, size_t count)
// {
//     __asm__(R"(
//     push %rbp
//     mov %rbp, %rsp
//     )");

//     __asm__(R"(
//     mov QWORD PTR %[%rbp+10],%rcx
//     mov QWORD PTR %[%rbp+18],%rcx
//     mov QWORD PTR %[%rbp+20],%rcx
//     mov QWORD PTR %[%rbp+28],%rcx
//     )");

//     // rax or rcx - function
//     // rdx - values
//     // r8 - sizes
//     // r9 - count 
//     __asm__(""\
//     "           \n"\
//     "           \n"\
//     "           \n"\
//     "           \n"\
//     "           \n"\
//     "           \n"\
//     "           \n"\
//     "           \n"\
//     "           \n"\
//     );


//     __asm__(R"(
//     pop %rbp
//     ret
//     )");
// }

#endif