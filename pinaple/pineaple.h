#ifndef _PINEAPLE_H_
#define _PINEAPLE_H_

#include <stdint.h>
#include <stdlib.h>

#include "paged.h"

#pragma region storage

/**
 * @brief storage stores data
 * 
 */
typedef struct 
{
    size_t count; ///< counts how many there are

    int * needs_free;
    size_t * size;
    void ** ptr;
} Storage;

/// @brief used for type safety
typedef struct Paged PStorage;

PStorage * storage_new();
PStorage * storage_copy(PStorage * other);
void storage_free(PStorage * other);

size_t storage_copyTo(PStorage * storage, void * data, size_t size);
void * storage_alloc(PStorage * storage, size_t size, size_t * id);
void storage_delete(PStorage * storage, size_t id);

size_t storage_add(PStorage * storage, void * ptr, size_t size);
void storage_remove(PStorage * storage, void * ptr);

#pragma endregion

#pragma region stack

typedef struct
{
    size_t iCount;
    size_t dCount;
    size_t rCount;

    uint32_t ** iStack;
    uint32_t ** dStack;
    uint32_t ** rStack;
} Stack;

/// @brief used for type safety
typedef struct Paged PStack;

void stack_pushFN();
void stack_pushData();
void stack_pushReturn();
void stack_pop();
void stack_popFN();
void stack_popFNandExecute();

#pragma endregion

#pragma region nameDB

typedef struct 
{
    size_t count;
    size_t * size;

    char ** names;
    uint32_t * id;
    Stack ** stack;
} NameDB;

/// @brief used for type safety
typedef struct Paged PNameDB;

void nameDB_addName(char * name, uint32_t id);
void nameDB_rename(uint32_t id, char * newName);
void nameDB_changeID(uint32_t oldId, uint32_t newId);
void nameDB_changeIDbyName(char * name, uint32_t newId);
void nameDB_removeName(char * name, uint32_t id);

#pragma endregion

#pragma region pineaple

typedef struct  
{
    Stack * rootStack;
    Stack * stack;
} Pineaple;

/// @brief used for type safety
typedef struct Paged PPineaple;

void pineaple_run(Pineaple * vm);

#pragma endregion


#endif