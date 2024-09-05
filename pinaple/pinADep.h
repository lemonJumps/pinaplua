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

enum pinADvarType
{
    pinADVT_integral = 0,
    pinADVT_float = 1,
    pinADVT_double = 2,
    pinADVT_vect256,
};

/**
 * @brief call function with the windows call semantics
 * 
 * @param function function pointer to be called, can be any executable address
 * @param values array of size_t values, passed as parameters.
 * @param types contains types of variable, differs for every architecture and call type
 * @param count count of parameters
 * @return void * con
 */
STDCALL void * pinADcallWIN(void * function, size_t * values, size_t * types, size_t count);