
#include <stdio.h>

#include "pagedTest.h"

#include "paged.h"
#include "tests.h"

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
    printf("paged memory tests\n");

    {
        struct pinPaged * mem = pinPInit(32);

        long long a = 8;

        TEST(mem->magic == __magic_value, "magic is correct", "magic is incorrect")
        TEST(mem->descriptorCount == 0, "descriptor count is 0", "descriptor count is incorrect")
        TEST(mem->next == NULL, "next is null", "next is not null")
        TEST(mem->previous == NULL, "previous is null", "previous is not null")
        TEST(mem->last == mem, "last is set to current element", "last is incorrect")

        pinPAdd(mem, &a, sizeof(a));
        pinPAdd(mem, &a, sizeof(a));
        pinPAdd(mem, &a, sizeof(a));
        pinPAdd(mem, &a, sizeof(a));

        TEST(mem->takenSize == 32, "4 integers allocated correctly", "failed to allocate 4 integers");

        pinPRem(mem, 3);

        TEST(mem->takenSize == 24, "integer removed", "integer wasn't removed");
        TEST(mem->descriptors[3].magic != __magic_value, "last element devalued properly", "last element has valid magic");

        pinPAdd(mem, &a, sizeof(a));
        pinPAdd(mem, &a, sizeof(a));

        pinPRem(mem, 0);
        pinPRem(mem, 1);
        pinPRem(mem, 2);

    }
}