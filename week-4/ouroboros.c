#include <stdio.h>

int main(void)
{
    int a = 0;
    int *b = &a;
    int * *c = &b;
    int * * *d = &c;
    int * * * *e = &d;
    int * * * * *f = &e;
    int * * * * * *g = &f;
    int * * * * * * *h = &g;
    int * * * * * * * *i = &h;

    printf("%i\n", ********i);
}