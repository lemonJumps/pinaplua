/**
 * @file pinlock.h
 * @author Lemon Jumps
 * @brief 
 * @version 0.1
 * @date 2024-08-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifdef __STDC_VERSION__
#if __STDC_VERSION__ >= 201112L
#ifndef __STDC_NO_ATOMICS__
// c  atomics can be used :D
#define C11_ATOM
#endif
#endif
#endif

#include <stdbool.h>

#ifdef C11_ATOM

#include <stdatomic.h>

typedef atomic_int lockType;

#else

typedef volatile int lockType;

#endif

// default implementation, uses boolean
void createLock(lockType * lock);
void destroyLock(lockType * lock);

bool lock(lockType * lock);
bool unlock(lockType * lock);

bool checkLocked(lockType * lock);
