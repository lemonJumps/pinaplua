
#include "pinConfig.h"
#include "nameDB.h"
#include "stdlib.h"
#include "string.h"

PINAPLE_VM_ERR_PRE_REQUISITES

#define __magic_value 0x0FFE4146UL

void init_NDBnode(struct _NDBnode * node)
{
    node->ptr = NULL;
    node->nodes = MALLOC(sizeof(struct _NDBnode) * 0xff);
    memset(node->nodes, 0, sizeof(struct _NDBnode) * 0xff);
    node->parent = NULL;
    node->magic = __magic_value;
    node->state = _NDBstate_empty;
}

void deinit_NDBnode(struct _NDBnode * node)
{
    // keep parent in tact for ease of use
    node->ptr = NULL;
    FREE(node->nodes);
    memset(node->nodes, 0, sizeof(struct _NDBnode) * 0xff);

    // change magic to indicate dead branch
    node->magic = 0xDEADBEEE;
}

struct nameDB * nameDBinit()
{
    struct nameDB * DB = MALLOC(sizeof(struct nameDB)); 
    
    init_NDBnode(&DB->root);
    
    return DB; 
}

void nameDBsetName(struct nameDB * DB, char * name, void * ptr)
{
    struct _NDBnode * node = &DB->root;
    char * c = name;

    // go trough nodes and make path to end node
    while (1)
    {
        if( node->nodes[*c].magic != __magic_value)
        {
            // indicate that node now contains children
            node->state |= _NDBstate_hasChildren;
            init_NDBnode(&node->nodes[*c]);
        }


        if (*(c+1) == 0)
        {
            node->state |= _NDBstate_hasValue;
            node->ptr = ptr;
            return;
        }
        
        node = &node->nodes[*c];
        c++;
    }
}

void * nameDBsetNameGetValue(struct nameDB * DB, char * name, void * ptr)
{
    struct _NDBnode * node = &DB->root;
    char * c = name;

    // go trough nodes and make path to end node
    while (1)
    {
        if( node->nodes[*c].magic != __magic_value)
        {
            // indicate that node now contains children
            node->state |= _NDBstate_hasChildren;
            init_NDBnode(&node->nodes[*c]);
        }

        if (*(c+1) == 0)
        {
            if (node->state & _NDBstate_hasValue)
            {
                node->state |= _NDBstate_hasValue;
                void * tmp = node->ptr;
                node->ptr = ptr;
                return tmp;
            }
            else
            {
                node->state |= _NDBstate_hasValue;
                node->ptr = ptr;
                return NULL;
            }
        }
        node = &node->nodes[*c];
        c++;
    }
}

void nameDBchangeName(struct nameDB * DB, char * name, char * newName)
{
    struct _NDBnode * node = &DB->root;
    char * c = name;

    while (1)
    {
        if (node->nodes[*c].magic != __magic_value)
        {
            return; // value not found
        }

        if (*(c+1) == 0)
        {
            break; // value found
        }
        node = &node->nodes[*c];
        c++;

    }

    // remove value flag
    node->state &= ~ _NDBstate_hasValue;
    
    void * value = node->ptr;

    // purge all nodes that are not used
    while(1)
    {
        // if either flag is presend stop
        if (node->state & (_NDBstate_hasChildren | _NDBstate_hasValue))
        {
            break;
        }

        deinit_NDBnode(node);
        node = node->parent;
    }

    nameDBsetName(DB, newName, value);
}

void nameDBremoveName(struct nameDB * DB, char * name)
{
    struct _NDBnode * node = &DB->root;
    char * c = name;

    while (1)
    {
        if (node->nodes[*c].magic != __magic_value)
        {
            return; // value not found
        }

        if (*(c+1) == 0)
        {
            break; // value found
        }
        node = &node->nodes[*c];
        c++;

    }

    // remove value flag
    node->state &= ~ _NDBstate_hasValue;

    // purge all nodes that are not used
    while(1)
    {
        // if either flag is presend stop
        if (node->state & (_NDBstate_hasChildren | _NDBstate_hasValue))
        {
            return;
        }

        deinit_NDBnode(node);
        node = node->parent;
    }
}

int nameDBgetPtr(struct nameDB * DB, char * name, void ** result)
{
    struct _NDBnode * node = &DB->root;
    char * c = name;

    while (1)
    {
        if (node->nodes[*c].magic != __magic_value)
        {
            return 1; // value not found
        }

        if (*(c+1) == 0)
        {
            *result = node->ptr;
            return 0; // value found
        }
        node = &node->nodes[*c];
        c++;
    }
}


void nameDBdestroy(struct nameDB * DB)
{
    FREE(DB);
}