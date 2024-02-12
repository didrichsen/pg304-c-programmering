#include <stdlib.h>
#include <stdio.h>

void randomFunction(int **doublePointerTest);

int main(int argc, char* argv[]) {

    int variable = 20;

    int *pSingle = &variable;

    int **pDouble = &pSingle;

    printf("pDouble = %d\n", **pDouble);

    printf("pSingle Address = %p\n", *pDouble);

    printf("pVariable = %d\n", *pSingle);

    randomFunction(&pSingle);


    return 0;

}

void randomFunction(int **doublePointerTest){

    int *p = *doublePointerTest;

    //This worked because doublePointerTest is giving *p the address it stores to the pointer.
    printf("%d",*p);
    //This worked because **doublePointerTest will be accessing the value of the pointer is points to.
    printf("%d",**doublePointerTest);

}
