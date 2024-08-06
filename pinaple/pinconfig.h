#ifndef _PINCONFIG_H_
#define _PINCONFIG_H_

#define WARNING(_msg) WARNING_FUNC(_msg, __LINE__, __FILE__)
#define WARNING_FUNC(_msg, _line, _file)

#define ERROR(_msg) ERROR_FUNC(_msg, __LINE__, __FILE__)
#define ERROR_FUNC(_msg, _line, _file)

/**
 * @brief defines the default size of storage to reserve when calling @ref storage_reserve with size of 0
 * 
 */
#define PINAPLE_VM_STORAGE_DEFAULT 128

#define CALLOC(n, s) calloc(n, s)
#define MALLOC(s) malloc(s)
#define FREE(p) free(p)

#endif