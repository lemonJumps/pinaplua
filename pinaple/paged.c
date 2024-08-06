#include "paged.h"
#include <stdint.h>

#include "pinconfig.h"
#include "memory.h"

// you may notice that this looks awfully like OOP.. that's because it is :D

void * _paged_alloc(
    int (*isFull)(Paged * paged, size_t reservedSize),
    int (*isEmpty)(Paged * paged, size_t reservedSize),
    void (*allocate)(Paged * paged, size_t size),
    void (*deallocate)(Paged * paged),
    size_t size)
{
    Paged * ptr = MALLOC(sizeof(Paged));
    ptr->isFull = isFull;
    ptr->isEmpty = isEmpty;
    ptr->allocate = allocate;
    ptr->deallocate = deallocate;
    ptr->next = NULL;
    ptr->last = NULL;

    ptr->allocate(ptr, size);

    return ptr;
}

void _paged_delete(Paged * paged)
{
    if (paged->deallocate == NULL)
    {
        ERROR("paged - deallocate is not assigned");
        return;
    }

    paged->deallocate(paged);
    FREE(paged);
}

void paged_expand(Paged * paged)
{
    Paged * ptr = paged;

    // go to last element
    while (ptr != NULL) {ptr = ptr->next;}

    ptr->next = _paged_alloc(ptr->isFull, ptr->isEmpty, ptr->allocate, ptr->deallocate, );
}

void paged_checkSpace(Paged * paged)
{

    Paged * ptr = paged;

    // go to last element
    while (ptr != NULL) {ptr = ptr->next;}

    if (ptr->isFull == NULL)
    {
        ERROR("paged - isFull is not assigned");
        return;
    }
    
    if (ptr->isEmpty == NULL)
    {
        ERROR("paged - isEmpty is not assigned");
        return;
    }

    if (ptr->isFull(ptr) > 0)
    {
        paged_expand(ptr);
    }
    else if (ptr->isEmpty(ptr) > 0)
    {
        // keep at least one
        if (ptr->next != NULL && ptr->last != NULL)
        {
            _paged_delete(ptr);
        }
    }
    
}

Paged * paged_new(
    int (*isFull)(Paged * paged),
    int (*isEmpty)(Paged * paged),
    void (*allocate)(Paged * paged, size_t size),
    void (*deallocate)(Paged * paged),
    size_t size
    )
{
    return _paged_alloc(isFull, isEmpty, allocate, deallocate, size);
}

void paged_delete(Paged * paged)
{
    Paged * ptr = paged;

    // go to last element
    while (ptr != NULL) {ptr = ptr->next;}

    // remove elements from back to front
    while (ptr != NULL) {
        void * tp = ptr;
        ptr = ptr->last;
        _paged_delete(tp);
    }
}
