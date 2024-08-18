#include <string.h>
#include <stdio.h>


void multiFunc(char a, int b, double c)
{
    volatile int a = 0;
}

const int fnA(int i) {return i;}
int fnB(int i) {return i;}
int fnC() {return 3;}

void fnD() {}

int main (void)
{
    const char * hi = "Hello World 😈🐱‍💻";
    printf(hi);

    int array[20] = {123,456};

    int i = 10; int j = 20; int k = 25;

    {
        int bone = 25;
    }

    int l = i + j * k / l % j;

    i *= 78;

    fnA(fnB(fnC()));

    return i + ((j + k) + l);
}
