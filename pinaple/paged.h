#ifndef _PAGED_H_
#define _PAGED_H_

#include <stdint.h>
#include <stddef.h>

/**
 * @brief sotres paged memory
 * 
 * allocating more pages:
 * 
 * 
 */
struct Paged
{
size_t reservedSize;
    
int (*isFull)(struct Paged * paged);
int (*isEmpty)(struct Paged * paged);
void (*allocate)(struct Paged * paged, size_t size);
void (*deallocate)(struct Paged * paged);

void * ptr;

struct Paged * next;
struct Paged * last;
};

void paged_expand(struct Paged * paged);

struct Paged * paged_checkSpace(struct Paged * paged);

struct Paged * paged_new(
    int (*isFull)(struct Paged * paged),
    int (*isEmpty)(struct Paged * paged),
    void (*allocate)(struct Paged * paged, size_t size),
    void (*deallocate)(struct Paged * paged),
    size_t size
    );

void paged_delete(struct Paged * paged);

#endif
