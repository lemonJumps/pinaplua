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

/**
 * @brief call function with the windows call semantics
 * 
 * @param function function pointer to be called, can be any executable address
 * @param values array of size_t values, passed as parameters.
 * @param sizes array of sizes of parameters, allowed sizes are: 1, 2, 4, 8
 * @param count count of parameters
 * @return STDCALL* 
 */
STDCALL void * pinADcallWIN(void * function, size_t * values, size_t * sizes, size_t count);