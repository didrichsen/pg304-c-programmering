#include <stdio.h>

int main(int argc, char* argv[]) {

    int array[10];

    int *p;

    p = &array[0];

    array[0] = 10;
    array[1] = *p * 2;

    printf("The pointer is pointing to address %p with the value of %d\n", p,*p);

    int x = *p;

    printf("Value of x are copied from *p, so x = %d\n", x);

    int xPlusOne = *(p+1);

    printf("xPlusOne now has the value thats stored next to a[0] which is %d \n", xPlusOne);

}