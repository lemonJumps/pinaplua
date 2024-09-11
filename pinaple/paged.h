/**
 * @file paged.h
 * @author Lemon Jumps (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _PAGED_H_
#define _PAGED_H_

#include <stddef.h>
#include <stdint.h>

struct _pinPvar{
    void * startingAddress;
    size_t position;
    size_t size;
    uint32_t magic;
};

struct pinPaged{
    char * data;

    struct pinPaged * next;
    struct pinPaged * previous;
    struct pinPaged * last;

    struct _pinPvar * descriptors;

    size_t idOffset;
    size_t descriptorCount;
    size_t takenSize;
    size_t size;
    uint32_t magic;
};

/**
 * @brief initialize paged memory structure
 * 
 * @param paged structure to be initialized
 */
struct pinPaged *  pinPInit(size_t size);

/**
 * @brief add variable into the last page in paged
 * 
 * if variable cannot fit into page, it will allocate another page for it
 * 
 * @param paged page to do operations on
 * @param data if not null, copies data from pointer
 * @param size data size in bytes
 * @return size_t ID of variable
 */
size_t pinPAdd(struct pinPaged * paged, void * data, size_t size);

/**
 * @brief remove variable from page
 * 
 * 
 * 
 * @param paged page to do operations on
 * @param id id of variable to remove
 */
void pinPRem(struct pinPaged * paged, size_t id);

/**
 * @brief 
 * 
 * @param paged 
 */
void pinPDestroy(struct pinPaged * paged);

/**
 * @brief 
 * 
 * @param paged 
 */
void pinPDefrag(struct pinPaged * paged);

/**
 * @brief 
 * 
 * @param paged 
 * @param id 
 * @param value 
 */
void pinPSet(struct pinPaged * paged, size_t id, void * value);

/**
 * @brief 
 * 
 * @param paged 
 * @param id 
 * @param result 
 */
void pinPGet(struct pinPaged * paged, size_t id, void * result);

/**
 * @brief 
 * 
 * @param paged 
 * @param id 
 * @return void* 
 */
void * pinPGetPtr(struct pinPaged * paged, size_t id);

/**
 * @brief 
 * 
 * @param paged 
 * @param ptr 
 * @param size 
 */
void pinPCheckPtr(struct pinPaged * paged, void * ptr, size_t size);

/**
 * @brief 
 * 
 * @param paged 
 * @param ptr 
 * @param size 
 * @param id 
 */
void pinPCheckPtrID(struct pinPaged * paged, void * ptr, size_t size, size_t id);

/**
 * @brief 
 * 
 * @param paged 
 * @param fnPtr 
 */
void pinPRegisterMemMoveCallback(struct pinPaged * paged, void(* fnPtr)(size_t id, void * ptr, size_t size));

/**
 * @brief 
 * 
 * @param paged 
 * @param fnPtr 
 */
void pinPRegisterMemDeleteCallback(struct pinPaged * paged, void(* fnPtr)(size_t id, void * ptr, size_t size));

/**
 * @brief internal method for initializing variable descriptor
 * 
 * @param pVar 
 */
void _pinPvarInit(struct _pinPvar * pVar, void * address, size_t pos, size_t size);

#endif