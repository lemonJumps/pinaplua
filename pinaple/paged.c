#include "paged.h"
#include <stdint.h>

#include "pinconfig.h"
#include <memory.h>
#include <stdlib.h>

// you may notice that this looks awfully like OOP.. that's because it is :D

void * _paged_alloc(
    int (*isFull)(struct Paged * paged),
    int (*isEmpty)(struct Paged * paged),
    void (*allocate)(struct Paged * paged, size_t size),
    void (*deallocate)(struct Paged * paged),
    size_t size)
{
    struct Paged * ptr = MALLOC(sizeof(struct Paged));
    ptr->isFull = isFull;
    ptr->isEmpty = isEmpty;
    ptr->allocate = allocate;
    ptr->deallocate = deallocate;
    ptr->next = NULL;
    ptr->last = NULL;

    ptr->allocate(ptr, size);

    return ptr;
}

void _paged_delete(struct Paged * paged)
{
    if (paged->deallocate == NULL)
    {
        ERROR("paged - deallocate is not assigned");
        return;
    }

    paged->deallocate(paged);
    FREE(paged);
}

void paged_expand(struct Paged * paged)
{
    struct Paged * ptr = paged;

    // go to last element
    ptr = paged_getLast(ptr);

    ptr->next = _paged_alloc(ptr->isFull, ptr->isEmpty, ptr->allocate, ptr->deallocate, ptr->reservedSize);
}

struct Paged * paged_checkSpace(struct Paged * paged)
{

    struct Paged * ptr = paged;

    // go to last element
    ptr = paged_getLast(ptr);

    if (ptr->isFull == NULL)
    {
        ERROR("paged - isFull is not assigned");
        return NULL;
    }
    
    if (ptr->isEmpty == NULL)
    {
        ERROR("paged - isEmpty is not assigned");
        return NULL;
    }

    if (ptr->isFull(ptr) > 0)
    {
        paged_expand(ptr);
        ptr = paged_getLast(ptr);
    }
    else if (ptr->isEmpty(ptr) > 0)
    {
        // keep at least one
        if (ptr->next == NULL && ptr->last != NULL)
        {
            struct Paged * rptr = ptr->last;
            
            _paged_delete(ptr);

            return rptr;
        }
    }
    
    return ptr;
}

struct Paged * paged_new(
    int (*isFull)(struct Paged * paged),
    int (*isEmpty)(struct Paged * paged),
    void (*allocate)(struct Paged * paged, size_t size),
    void (*deallocate)(struct Paged * paged),
    size_t size
    )
{
    struct Paged * ptr = _paged_alloc(isFull, isEmpty, allocate, deallocate, size);

    return ptr;
}

void paged_delete(struct Paged * paged)
{
    struct Paged * ptr = paged;

    // go to last element
    ptr = paged_getLast(ptr);

    // remove elements from back to front
    while (ptr != NULL) {
        void * tp = ptr;
        ptr = ptr->last;
        _paged_delete(tp);
    }
}

struct Paged * paged_getLast(struct Paged * paged)
{
    struct Paged * ptr = paged;
    struct Paged * nptr = paged;
    while (nptr != NULL) {
        ptr = nptr;
        nptr = nptr->next;
        }

    return ptr;
}