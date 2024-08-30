#ifndef _DBGLIB_H_
#define _DBGLIB_H_


#include <stddef.h>

#ifdef DEBUG
    #define testPtr(x) _testPtr(x, sizeof(x))
#else
    #define testPtr(x)
#endif

void _testPtr(void * ptr, size_t size);


#endif