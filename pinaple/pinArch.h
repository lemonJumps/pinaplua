/**
 * @file pinArch.h
 * @author Lemon Jumps (you@domain.com)
 * @brief gets which architecture is used
 * @version 0.1
 * @date 2024-08-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _PINARCH_H_
#define _PINARCH_H_


#if defined(__x86_64__) || defined(_M_X64)
#define __PIN_ARCH_AMD64__
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
#define __PIN_ARCH_X86__
#elif defined(__arm__)
#define __PIN_ARCH_ARM__
#elif defined(__aarch64__) || defined(_M_ARM64)
#define __PIN_ARCH_ARM64__
#elif defined(mips) || defined(__mips__) || defined(__mips)
#define __PIN_ARCH_POWERPC__
#elif defined(__sh__)
#define __PIN_ARCH_SUPERH__
#elif defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
#define __PIN_ARCH_POWERPC__
#elif defined(__PPC64__) || defined(__ppc64__) || defined(__powerpc64__) || defined(_ARCH_PPC64)
#define __PIN_ARCH_POWERPC64__
#elif defined(__sparc__) || defined(__sparc)
#define __PIN_ARCH_SPARC__
#elif defined(__m68k__)
#define __PIN_ARCH_M68K__
#else
#define __PIN_ARCH_UNKNOWN__
#endif

#endif