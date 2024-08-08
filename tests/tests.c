
#include "pineaple.h"
#include <stdio.h>
#include <string.h>


#ifdef _WIN32
#include <Windows.h>
#endif

size_t sucessCount = 0;
size_t failCount = 0;

void END_TEST()
{
    printf("\ntests Succeded \t\t %d/%d\n", sucessCount, sucessCount+failCount);
    printf("tests Failed \t\t %d/%d\n", failCount, sucessCount+failCount);

    if (failCount == 0) 
    { 
        printf("===========================\n"); 
        printf("o(￣▽￣)ｄ ALL TESTS PASSED\n"); 
        printf("===========================\n"); 
    } 
    else 
    { 
        printf("===============================\n"); 
        printf("(≧﹏ ≦) some tests have failed\n"); 
        printf("===============================\n"); 
    } 
}

#define TEST(_x, _correct, _incorrect) \
    if (_x) \
    { printf("\t✔ " _correct "\n"); \
    sucessCount+=1; \
    } else { printf("\t❌ " _incorrect "\n"); \
    failCount+=1; \
    }

int main(void)
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        setvbuf(stdout, NULL, _IOFBF, 1000);
    #endif


    printf("unit-test \n pinaple::storage\n");

    {
        const char * test1 = "test string 1";

        PStorage * storage = storage_new();

        // allocate storage
        size_t id;
        const char * pt = storage_alloc(storage, strlen(test1), &id);

        Storage * s  = ((Storage *)storage->ptr);
        TEST(s != NULL, "storage is allocated", "storage is null")



        storage_free(storage);
    }

    END_TEST();

    return 0;
};