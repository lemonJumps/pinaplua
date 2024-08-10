
#include "pineaple.h"
#include <stdio.h>
#include <string.h>


#ifdef _WIN32
#include <Windows.h>

#include "windows.h"
#include "psapi.h"

size_t get_ram_usage()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
    return virtualMemUsedByMe;
}

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
    { printf("\t✅ " _correct "\n"); \
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

    printf("sanity check:\n");

    TEST(1, "test succeded sucessfully", "test wrongfully failed")
    TEST(0, "test wrongfully succeded", "test failed sucesfully")
    sucessCount = 0;
    failCount = 0;
    printf("\n\n");

    printf("unit-test \n pinaple::storage\n");

    {
        printf("  first element test\n");

        const char * test1 = "test string 1";

        PStorage * storage = storage_new();

        // allocate storage
        size_t id;
        const char * pt = storage_alloc(storage, strlen(test1), &id);

        Storage * s  = ((Storage *)storage->ptr);
        TEST(s != NULL, "storage is allocated", "storage is null")
        TEST(s->count == 1, "one element is allocated", "wrong number of allocated items")
        TEST(s->needs_free[0] > 0, "element 0 needs free", "element 0 isn't marked as needs free")
        TEST(s->size[0] == strlen(test1), "element 0 length is correct", "element 0 length is wrong")
        TEST(id == 0, "ID is returned as id 0", "ID returned is wrong")

        memcpy(pt, test1, strlen(test1));


        printf("  second element test\n");

        id = storage_copyTo(storage, pt, strlen(pt));

        TEST(s->count == 2, "two elements are allocated", "wrong number of allocated items")
        TEST(s->needs_free[1] > 0, "element 1 needs free", "element 1 isn't marked as needs free")
        TEST(s->size[1] == strlen(test1), "element 1 length is correct", "element 1 length is wrong")
        TEST(id == 1, "ID is returned as id 1", "ID returned is wrong")


        // allocate lots of ram
        for (size_t i = 0; i < 5000; i++)
        {
            size_t dummy;
            storage_alloc(storage, 20, dummy);
        }

        // check if memory is decreased by free
        {
            size_t before;
            size_t after; 

            before = get_ram_usage();
            storage_free(storage);
            after = get_ram_usage();

            printf("%i %i\n", before, after);
        }
    }

    END_TEST();

    return 0;
};