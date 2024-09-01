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

#define __magic_value 0xBEEF420BUL

struct pinPaged{


    uint32_t magic;
};

/**
 * @brief initialize paged memory structure
 * 
 * @param paged structure to be un initialized
 */
void pinPInit(struct pinPaged * paged);

/**
 * @brief 
 * 
 * @param paged 
 * @param data 
 * @param size 
 * @return size_t 
 */
size_t pinPAdd(struct pinPaged * paged, void * data, size_t size);

/**
 * @brief 
 * 
 * @param paged 
 * @param id 
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

#endif