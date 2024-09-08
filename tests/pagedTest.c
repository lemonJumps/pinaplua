
#include <stdio.h>

#include "pagedTest.h"

#include "paged.h"

void printDescriptor(struct _pinPvar * desc)
{
    printf("## descriptor ##\n");
    printf(" address: %x\n", desc->startingAddress);
    printf(" position: %i\n", desc->position);
    printf(" size: %i\n", desc->size);
    printf(" data: ");

    if (desc->magic == __magic_value)
    {
        for (size_t i = 0; i < desc->size; i++)
        {
            printf("%x ", ((char *)desc->startingAddress)[i]);
        }
    }else{
        printf("bad magic");
    }
    printf("\n");
}

void printMemory(struct pinPaged * mem)
{
    printf("### memory print ###\n");
    printf(" size: %i\n", mem->size);
    printf(" taken: %i\n", mem->takenSize);
    printf(" descriptorCount: %i\n", mem->descriptorCount);

    for (size_t i = 0; i < mem->descriptorCount; i++)
    {
        printDescriptor(&mem->descriptors[i]);
    }
    printf("\n");

    if (mem->next)
    {
        printMemory(mem->next);
    }
}

void pagedTest()
{
    {
        struct pinPaged * mem = pinPInit(32);

        long long a = 8;

        pinPAdd(mem, &a, sizeof(a));
        pinPAdd(mem, &a, sizeof(a));
        pinPAdd(mem, &a, sizeof(a));
        pinPAdd(mem, &a, sizeof(a));

        printMemory(mem);

        pinPRem(mem, 3);

        printMemory(mem);

        pinPAdd(mem, &a, sizeof(a));
        pinPAdd(mem, &a, sizeof(a));

        printMemory(mem);

        pinPRem(mem, 0);
        pinPRem(mem, 1);
        pinPRem(mem, 2);

        printMemory(mem);
    }
}