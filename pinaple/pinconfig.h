/**
 * @file pinConfig.h
 * @author Lemon Jumps (you@domain.com)
 * @brief pinaple VM configuration
 * @version 0.1
 * @date 2024-09-11
 * 
 * @copyright Copyright (c) 2024
 * 
 * On the usage of note, warning, error:
 * 
 * Since these are defines, placing __file__ and __line__ besides them lets you return file and line where error happened.
 * 
 * If error handling requires aditional files, defines etc, place them into @ref PINAPLE_VM_ERR_PRE_REQUISITES
 * this define is inserted into every file that calls @ref PINAPLE_VM_ERROR ,  @ref PINAPLE_VM_WARNING or @ref PINAPLE_VM_NOTE
 */

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

#define PINAPLE_VM_ERR_PRE_REQUISITES

/**
 * @brief notes are informative, and mostly inform about side effects
 * 
 * So for instance if paged runs out of page memory and allocates a new page.
 * think of it as rare events
 * 
 * @param x - message containing what happened
 * @param p1 - pointer 1 will contain value that ties to the error
 * @param p2 - same as p1
 * @param i1 - integer 1 will contain some integral value that ties to the error
 * @param i2 - same as i1
 */
#define PINAPLE_VM_NOTE(x, p1, p2, i1, i2)

/**
 * @brief warning happens when something doesn't run as expected
 * 
 * For example if you try to find a value, and it doesn't exist, it doesn't mean the VM is broken.
 * But it means the value isn't there.
 * 
 * Warnings are not nesceserily bad, and the developer should decide wether a warnin is bad or not.
 * Treating all warnings as errors in the context of the VM is wrong and will result in poor choises.
 */
#define PINAPLE_VM_WARNING(x, p1, p2, i1, i2)

/**
 * @brief error is only triggered if something bad happens within the VM, like bad magic etc
 *
 * Errors are definitely bad, if an error is encountered, first see where exactly it occured,
 * and then try to fix it.
 * 
 * The most common error in code is bad/missing resources, every resource has its own magic number, that is used to check if its correct.
 * If magic error occures, it's most likely caused by resource being used after it was freed.
 * 
 */
#define PINAPLE_VM_ERROR(x, p1, p2, i1, i2)

#define CALLOC(n, s) calloc(n, s);
#define MALLOC(s) malloc(s);
#define FREE(p) free(p);

#endif