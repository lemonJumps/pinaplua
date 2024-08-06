#ifndef _PAGED_H_
#define _PAGED_H_

#include <stdint.h>

/**
 * @brief sotres paged memory
 * 
 * allocating more pages:
 * 
 * 
 */
typedef struct
{
size_t reservedSize;
    
int (*isFull)(Paged * paged);
int (*isEmpty)(Paged * paged);
void (*allocate)(Paged * paged, size_t size);
void (*deallocate)(Paged * paged);

void * ptr;

Paged * next;
Paged * last;
} Paged;

void paged_expand(Paged * paged);

void paged_checkSpace(Paged * paged);

Paged * paged_new(
    int (*isFull)(Paged * paged),
    int (*isEmpty)(Paged * paged),
    void (*allocate)(Paged * paged, size_t size),
    void (*deallocate)(Paged * paged),
    size_t size
    );

void paged_delete(Paged * paged);

#endif
