#include "pineaple.h"
#include "pinconfig.h"
#include <memory.h>
#include "paged.h"

/*

how to work this thing:

before the vm starts, register global things, variables, prebuilt classes.
first put them into storage and then put their name into NameDB.

if possible functions should be their own VMs, but could be just jumps;
since the VM is literally just an I D and R stack. 

NOW the stacks can be interchanged on the fly,
so, simple optimizations are possible

I mean complex optimizations are definitely possible, ESP when the code can be changed at runtime.

*/


#pragma region storage

int _storage_isFull(struct Paged * paged)
{
    return ((Storage *)paged->ptr)->count == paged->reservedSize;
}

int _storage_isEmpty(struct Paged * paged)
{
    return ((Storage *)paged->ptr)->count == 0;
}

void _storage_allocate(struct Paged * paged, size_t size)
{
    Storage * stor = MALLOC(sizeof(Storage));
    stor->count = 0;
    stor->needs_free = CALLOC(size, sizeof(int));
    stor->size = CALLOC(size, sizeof(size_t));
    stor->ptr = CALLOC(size, sizeof(void*));

    paged->ptr = stor;
}

void _storage_deallocate(struct Paged * paged)
{
    Storage * stor = ((Storage *)paged->ptr);
    for (size_t i = 0; i < stor->count; i++)
    {
        if (stor->needs_free[i] > 0)
        {
            FREE(stor->ptr[i]);
        }
    }
}

// constructor, destructor, copy
PStorage * storage_new()
{
    PStorage * ptr ;
    paged_new(
        _storage_isFull, 
        _storage_isEmpty, 
        _storage_allocate, 
        _storage_deallocate, 
        PINAPLE_VM_STORAGE_DEFAULT
        );
}

PStorage * storage_duplicate(PStorage * other)
{
    PStorage * paged = storage_new();
    Storage * stor = ((Storage *)paged->ptr);
    Storage * otherStor = ((Storage *)other->ptr);

    stor->count = otherStor->count;
    memcpy(stor->needs_free, otherStor->needs_free, stor->count * sizeof(int*));
    memcpy(stor->size, otherStor->size, stor->count * sizeof(size_t));
    memcpy(stor->ptr, otherStor->ptr, stor->count * sizeof(void*));
}

void storage_free(PStorage * storage)
{
    paged_delete(storage);
}


size_t storage_copyTo(PStorage * storage, void * data, size_t size)
{
    storage = paged_checkSpace(storage);

    Storage * stor = ((Storage *)storage->ptr);

    size_t i = stor->count++;
    stor->needs_free[i] = 1;
    stor->size[i] = size;
    stor->ptr[i] = MALLOC(size);

    memcpy(stor->ptr[i], data, size);

    return i;
}

void * storage_alloc(PStorage * storage, size_t size, size_t * id)
{
    storage = paged_checkSpace(storage);

    Storage * stor = ((Storage *)storage->ptr);

    size_t i = stor->count++;
    stor->needs_free[i] = 1;
    stor->size[i] = size;
    stor->ptr[i] = MALLOC(size);

    *id = i;

    return stor->ptr[i];
}

void storage_delete(PStorage * storage, size_t id)
{

}


size_t storage_add(PStorage * storage, void * ptr, size_t size)
{

}

void storage_remove(PStorage * storage, void * ptr)
{

}


#pragma endregion


#pragma region nameDB

void nameDB_addName(char * name, uint32_t id)
{

}

void nameDB_rename(uint32_t id, char * newName)
{

}

void nameDB_changeID(uint32_t oldId, uint32_t newId)
{

}

void nameDB_changeIDbyName(char * name, uint32_t newId)
{

}

void nameDB_removeName(char * name, uint32_t id)
{

}

#pragma endregion

#pragma region stack

void stack_pushFN()
{

}

void stack_pushData()
{

}

void stack_pushReturn()
{

}

void stack_pop()
{

}

void stack_popFN()
{

}

void stack_popFNandExecute()
{

}

#pragma endregion

#pragma region pineaple

void pineaple_run(Pineaple * vm)
{

}

#pragma endregion