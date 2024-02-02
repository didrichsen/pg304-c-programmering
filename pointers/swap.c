#include <stdio.h>

void swap(int *px, int *py){

    int temp;

    temp = *px;
    *px = *py;
    *py = temp;

}

int main(int argc, char* argv[]){

    int a = 10;
    int b = 20;

    swap(&a,&b);

    printf("a = %d, b = %d", a,b);

}