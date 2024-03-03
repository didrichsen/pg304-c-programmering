#include "bubblesort.h"
#include <stdio.h>

int main (void){

    unsigned int array[5] = {4,2,5,7,2};
    int size= sizeof (array) / sizeof (unsigned int);

    printf("%d\n",size);


    bubbleSort(array,size);


}