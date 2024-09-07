
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

int FCtest(int a, int b, int c, int e, int f)
{
    int ret = a + b + f + c + e;
    printf("value a: %i\n", a);
    printf("value b: %i\n", b);
    printf("value c: %i\n", c);
    printf("value e: %i\n", e);
    printf("value f: %i\n", f);

    return ret;
}

int FCtest2(long long a, float b, char c, int d, char e, char f)
{
    int ret = a + b + c + d + e + f;
    printf("value a: %i\n", a);
    printf("value b: %f\n", b);
    printf("value c: %i\n", c);
    printf("value d: %i\n", d);
    printf("value e: %i\n", e);
    printf("value f: %i\n", f);

    return ret;
}

int FCtest3(double a, float b, char c, int d, char e, double f)
{
    int ret = a + b + c + d + e + f;
    printf("value a: %f\n", a);
    printf("value b: %f\n", b);
    printf("value c: %i\n", c);
    printf("value d: %i\n", d);
    printf("value e: %i\n", e);
    printf("value f: %f\n", f);

    return ret;
}

int FCtest4(int a, int b, int c, int d, int e, int f)
{
    int ret = a + b + c + d + e + f;
    printf("value a: %i\n", a);
    printf("value b: %i\n", b);
    printf("value c: %i\n", c);
    printf("value d: %i\n", d);
    printf("value e: %i\n", e);
    printf("value f: %i\n", f);

    return ret;
}

int FCtest5(int a, int b)
{
    int ret = a + b;
    printf("value a: %i\n", a);
    printf("value b: %i\n", b);

    return ret;
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
        Sleep(150);

        TEST(checkLocked(&testLock) == 0, "lock is unset", "lock isn't set");

        pthread_join(thread, NULL);
    }

    {
        size_t values[] = {2, 3, 4, 5, 6};
        size_t sizes[] = {pinADVT_integral, pinADVT_integral, pinADVT_integral, pinADVT_integral, pinADVT_integral};
        size_t result = (size_t) pinADcallWIN(FCtest, values, sizes, 5);
    
        TEST(result == 2+3+4+5+6, "foreign call succeeded!", "foreign call failed")
    }

    {
        float a = 3.0;
        size_t values[] = {2, *((size_t*) &a), 4, 5, 6, 7};
        size_t sizes[] = {pinADVT_integral, pinADVT_float, pinADVT_integral, pinADVT_integral, pinADVT_integral, pinADVT_integral};
        size_t result = (size_t) pinADcallWIN(FCtest2, values, sizes, 6);
    
        TEST(result == 2+3+4+5+6+7, "foreign call succeeded!", "foreign call failed")
    }

    {
        double a = 2.0;
        float b = 3.0;
        double c = 7.0;
        size_t values[] = { *((size_t*) &a), *((size_t*) &b), 4, 5, 6, *((size_t*) &c)};
        size_t sizes[] = {pinADVT_double, pinADVT_float, pinADVT_integral, pinADVT_integral, pinADVT_integral, pinADVT_double};
        size_t result = (size_t) pinADcallWIN(FCtest3, values, sizes, 6);
    
        TEST(result == 2+3+4+5+6+7, "foreign call succeeded!", "foreign call failed")
    }

    {
        size_t values[] = {2, 3, 4, 5, 6, 7};
        size_t sizes[] = {pinADVT_integral, pinADVT_integral, pinADVT_integral, pinADVT_integral, pinADVT_integral, pinADVT_integral};
        size_t result = (size_t) pinADcallWIN(FCtest4, values, sizes, 6);
    
        TEST(result == 2+3+4+5+6+7, "foreign call succeeded!", "foreign call failed")
    }

    {
        size_t values[] = {2, 3};
        size_t sizes[] = {pinADVT_integral, pinADVT_integral};
        size_t result = (size_t) pinADcallWIN(FCtest5, values, sizes, 2);
    
        TEST(result == 2+3, "foreign call succeeded!", "foreign call failed")
    }

    END_TEST();

    return 0;
};