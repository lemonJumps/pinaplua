#include "pinlock.h"

#ifndef C11_ATOM

#include <stdatomic.h>
#include <stdbool.h>

// default implementation, uses boolean
void createLock(lockType lock)
{
    atomic_init(lock, 0);
}

void destroyLock(lockType lock)
{
    
}

bool lock(lockType lock)
{
    int val = 0;
    return atomic_compare_exchange_strong(lock, val, 1);
}

bool unlock(lockType lock)
{
    int val = 1;
    return atomic_compare_exchange_strong(lock, val, 0);
}

bool checkLocked(lockType lock)
{
    *lock > 0;
}

#else

// default implementation, uses boolean
void createLock(lockType lock)
{
    *lock = 0;
}

void destroyLock(lockType lock)
{
    
}

bool lock(lockType lock)
{
    if (*lock > 0) return false;
    *lock = 1;
    return true;
}

bool unlock(lockType lock)
{
    if (*lock == 0) return false;
    *lock = 0;
    return true;
}

bool checkLocked(lockType lock)
{
    return *lock > 0;
}

#endif