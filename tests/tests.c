
// #include "pineaple.h"
#include <stdio.h>
#include <string.h>


#include "pinlock.h"
#include "pthread.h"
#include "pinADep.h"

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

int _test(int i, int j)
{
    return i + j;
}

struct lockThread
{
    lockType * _lock;
    int * result;
};

void* checkLockThread(void * p)
{
    struct lockThread * lt = p;

    for (int i = 0; i < 20; i++)
    {
        // *(*lt).result = checkLocked((*lt)._lock);
        printf("%i",checkLocked((*lt)._lock));
        Sleep(10);
    }
    return NULL;
}

int testFunc(int a, int b)
{
    return a + b;
}

int main(void)
{
    volatile int a = _test(
        _test(1,2), _test(3,4)
    );

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

    printf("unit-test \n pinLock.h\n");

    {
        pthread_t thread;

        lockType testLock;
        struct lockThread lt;
        lt._lock = &testLock;

        createLock(&testLock);
        TEST(lock(&testLock) == 1, "lock sucess", "lock fail");

        TEST(checkLocked(&testLock) == 1, "lock is set", "lock isn't set");

        pthread_create(&thread, NULL, checkLockThread, &lt);

        Sleep(100);

        TEST(unlock(&testLock) == 1, "unlock sucess", "unlock fail");

        TEST(checkLocked(&testLock) == 0, "lock is unset", "lock isn't set");

        pthread_join(thread, NULL);
    }

    {
        int values[] = {2, 3};
        size_t sizes[] = {sizeof(int), sizeof(int)};
        pinADcallCDECL32(testFunc, values, sizes, 2);
    }

    END_TEST();

    return 0;
};