#include "pineaple.h"

/*

how to work this thing:

before the vm starts, register global things, variables, prebuilt classes.
first put them into storage and then put their name into NameDB.

if possible functions should be their own VMs, but could be just jumps;
since the VM is literally just an I D and R stack. NOW the stacks can be interchanged on the fly/
so, simple optimizations are possible

I mean complex optimizations are definitely possible, ESP when the code can be changed at runtime.

*/


#pragma region storage

size_t storage_copyTo(void * data, size_t size)
{

}

void * storage_alloc(size_t size, size_t * id)
{

}

void storage_delete(void * ptr)
{

}


size_t storage_add(void * ptr, size_t size)
{

}

void storage_remove(void * ptr)
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

void nameDB_changeID(char * name, uint32_t newId)
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