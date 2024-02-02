#include <stdio.h>

int main(int argc, char* argv[]) {

    int *p,*q;
    int a = 10;
    int b = 25;

    p = &a;
    q = &b;

    printf("p = %d, q = %d\n", *p,*q);

    *q = 15;

    printf("q = %d\n", *q);
}