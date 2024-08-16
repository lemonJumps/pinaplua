#include <string.h>
#include <stdio.h>

int fnA(int i) {return i;}
int fnB(int i) {return i;}
int fnC() {return 3;}

int main (void)
{
    const char * hi = "Hello World 😈🐱‍💻";
    printf(hi);

    int i = 10; int j = 20; int k = 25;

    int l = i + j * k;

    i *= 78;

    fnA(fnB(fnC()));

    return i + ((j + k) + l);
}
