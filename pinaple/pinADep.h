/**
 * @file pinADep.h
 * @author Lemon Jumps (you@domain.com)
 * @brief architecture dependent code
 * @version 0.1
 * @date 2024-08-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "pinArch.h"

#ifdef __PIN_ARCH_UNKNOWN__
#error unknown architecture, calls from VM are unsupported
#endif

#include <stddef.h>

#define STDCALL __attribute__((stdcall))

STDCALL void pinADcallWIN(void * function, void * values, size_t * sizes, size_t count);