
#include <stdint.h>

#pragma region storage

/**
 * @brief storage stores data
 * 
 */
typedef struct 
{
size_t count; ///< counts how

size_t * size;
void * ptr;

Storage * next;
Storage * last;
} Storage;


size_t storage_addData(void * data, size_t size);
void * storage_alloc(size_t size, size_t * id);
void storage_delete(void * ptr);

#pragma endregion

#pragma region nameDB

typedef struct 
{
size_t count;
size_t * size;

char ** names;
uint32_t * id;
Stack * stack;

NameDB * next;
NameDB * last;
} NameDB;

void nameDB_addName(char * name, uint32_t id);
void nameDB_rename(uint32_t id, char * newName);
void nameDB_changeID(uint32_t oldId, uint32_t newId);
void nameDB_changeID(char * name, uint32_t newId);
void nameDB_removeName(char * name, uint32_t id);

#pragma endregion

#pragma region stack

typedef struct
{
size_t reservedSize;

// size_t count;

size_t iCount;
size_t dCount;
size_t rCount;

uint32_t ** iStack;
uint32_t ** dStack;
uint32_t ** rStack;


Stack * next;
Stack * last;
} Stack;

void stack_pushFN();
void stack_pushData();
void stack_pushReturn();
void stack_pop();
void stack_popFN();
void stack_popFNandExecute();

#pragma endregion

#pragma region pineaple

typedef struct  
{
    Stack * rootStack;
    Stack * stack;
} Pineaple;

void pineaple_run(Pineaple * vm);

void pineaple_pushFunction(Pineaple * vm, void * function);
void pineaple_pushData(Pineaple * vm, void * function);
void pineaple_pushReturn(Pineaple * vm, void * function);

#pragma endregion


