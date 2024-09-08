/**
 * @file paged.c
 * @author Lemon Jumps (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include <string.h>

#include "paged.h"
#include "pinConfig.h"

struct pinPaged * pinPInit(size_t size)
{
    struct pinPaged * paged = MALLOC(sizeof(struct pinPaged));

    if (size == 0) {size = PINAPLE_VM_STORAGE_DEFAULT;}

    paged->data = MALLOC(size);
    paged->next = NULL;
    paged->previous = NULL;
    paged->last = paged;
    
    paged->descriptors = MALLOC(sizeof(struct _pinPvar) * size);

    memset(paged->descriptors, 0, sizeof(struct _pinPvar) * size);

    paged->idOffset = 0;
    paged->descriptorCount = 0;
    paged->takenSize = 0;
    paged->size = size;
    paged->magic = __magic_value;
}

size_t pinPAdd(struct pinPaged * paged, void * data, size_t size)
{
    // get thelast page
    paged = paged->last;

    // if there's no memory left, allocate new page
    if (size > (paged->size - paged->takenSize))
    {
        PINAPLE_VM_NOTE("adding new page");
        
        size_t nsize = paged->size;
        // if page is too big for default size, allocate bigger page
        if (size > nsize) 
        {
            // this might not be wrong, but it's definitely noteworthy
            PINAPLE_VM_WARNING("variable cannot fit into page, increasing size");
            nsize = size;
        }
        
        // change which page is used to another one
        struct pinPaged * lpaged = paged;
        paged = pinPInit(nsize);

        // connect all pages together
        lpaged->next = paged;
        paged->previous = lpaged;
        
        // add offset to page
        paged->idOffset = lpaged->descriptorCount + lpaged->idOffset;

        // iterate backwards trough all pages setting the new last value
        struct pinPaged * it = paged;
        while (it->previous != NULL)
        {
            it->last = paged;
            it = it->previous;
        }
    }

    struct _pinPvar * pVar = &paged->descriptors[paged->descriptorCount];
    _pinPvarInit(pVar, &paged->data[paged->takenSize], paged->takenSize, size);
    paged->takenSize += size;
    paged->descriptorCount++;

    // in case theres no data, don't copy it
    if (data != NULL)
    {
        PINAPLE_VM_NOTE("allocating data");
        memcpy(pVar->startingAddress, data, size);
    }

    return paged->descriptorCount-1;
}

void pinPRem(struct pinPaged * paged, size_t id)
{
    paged->descriptors[id].startingAddress = 0;
    paged->descriptors[id].magic = 0;

    // decrease count and remove trailing messages
    if (id+1 == paged->descriptorCount)
    {
        paged->takenSize -= paged->descriptors[id].size;
        while (1)
        {
            id--;

            if (paged->descriptors[id].magic == __magic_value)
            {
                paged->descriptorCount = id+1;
                return;
            }
            if (id == 0)
            {
                paged->descriptorCount = 0;
                return;
            }
            paged->takenSize -= paged->descriptors[id].size;
        }
    }
}

void pinPDestroy(struct pinPaged * paged)
{
    struct pinPaged * last = paged->last;

    while(last->next)
    {
        FREE(paged->data);
        FREE(paged->descriptors);
        last = last->next;
        FREE(last->next);
    }
}

void pinPDefrag(struct pinPaged * paged)
{
    // TODO: defragmentation
}

int _findValue(struct _pinPvar ** ptr, struct pinPaged * paged, size_t id)
{
    if (paged->magic != __magic_value)
    {
        PINAPLE_VM_ERROR("page has bad magic, on variable set");
        return 1;
    }

    while (1)
    {
        if (id < paged->descriptorCount + paged->idOffset)
        {
            break; // found
        }
        if (paged->next == NULL)
        {
            PINAPLE_VM_ERROR("variable id not found");
            return 2;
        }
        paged = paged->next;
    }

    struct _pinPvar * descriptor = &paged->descriptors[id - paged->idOffset];

    if (descriptor->magic != __magic_value)
    {
        PINAPLE_VM_ERROR("variable descriptor has bad magic, on variable set");
        return 3;
    }

    *ptr = descriptor;
    return 0;
}

void pinPSet(struct pinPaged * paged, size_t id, void * value)
{
    struct _pinPvar * descriptor;

    if (_findValue(&descriptor, paged, id))
    {
        return;
    }

    memcpy(descriptor->startingAddress, value, descriptor->size);
}

void pinPGet(struct pinPaged * paged, size_t id, void * result)
{
    struct _pinPvar * descriptor;

    if (_findValue(&descriptor, paged, id))
    {
        return;
    }

    memcpy(result, descriptor->startingAddress, descriptor->size);
}

void * pinPGetPtr(struct pinPaged * paged, size_t id)
{
    struct _pinPvar * descriptor;

    if (_findValue(&descriptor, paged, id))
    {
        return NULL;
    }

    return descriptor->startingAddress;
}

void _pinPvarInit(struct _pinPvar * pVar, void * address, size_t pos, size_t size)
{
    pVar->startingAddress = address;
    pVar->position = pos;
    pVar->size = size;
    pVar->magic = __magic_value;
}