/**
 * @file nameDB.h
 * @author Lemon Jumps
 * @brief 
 * @version 0.1
 * @date 2024-09-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _NAME_DB_H_
#define _NAME_DB_H_

#include <stdint.h>

enum _NDBstate
{
    _NDBstate_empty = 0,
    _NDBstate_hasValue = 1,
    _NDBstate_hasChildren = 2,
};

struct _NDBnode
{
    void * ptr;
    struct _NDBnode * nodes;
    struct _NDBnode * parent;
    uint32_t magic;
    uint8_t state;
};

struct nameDB
{
    struct _NDBnode root;
    size_t depth;
    uint32_t magic;
};


struct nameDB * nameDBinit();

/**
 * @brief Assigns value to name in a DB
 * 
 * 
 * @param DB - database to be used for storing data
 * @param name - name of the 
 * @param ptr 
 */
void nameDBsetName(struct nameDB * DB, char * name, void * ptr);

/**
 * @brief Same as @ref nameDBsetName, except it returns the old value as well
 * 
 * @param DB 
 * @param name 
 * @param ptr
 * @return returns value if there was a value before and NULL if there wasn't 
 */
void * nameDBsetNameGetValue(struct nameDB * DB, char * name, void * ptr);


void nameDBchangeName(struct nameDB * DB, char * name, char * newName);


void nameDBremoveName(struct nameDB * DB, char * name);


int nameDBgetPtr(struct nameDB * DB, char * name, void ** result);


void nameDBdestroy(struct nameDB * DB);


#endif