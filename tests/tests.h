
#include <stdio.h>

extern size_t sucessCount;
extern size_t failCount;

#define TEST(_x, _correct, _incorrect) \
    if (_x) \
    { printf("\t✅ " _correct "\n"); \
    sucessCount+=1; \
    } else { printf("\t❌ " _incorrect "\n"); \
    failCount+=1; \
    }

    