#include "bubblesort.h"

void swap (unsigned int *a, unsigned int *b);

void bubbleSort(unsigned int array[], int size){

    int i = 0, j = 0, temp = 0, p = 0;

    int swapped = FALSE;

    for(i = 0; i < size - 1; i++){
        swapped = FALSE;
        for(j = 0; j < size - i - 1; j++){
            if(array[j] > array[j + 1]){

                swap(&array[j], &array[j+1]);
                swapped = TRUE;
            }
        }
        if(!swapped){
            break;
        }
    }

}

void swap (unsigned int *a,unsigned int *b){

    unsigned int temp;

    unsigned int *pIntA = a;
    unsigned int *pIntB = b;

    temp = *pIntB;
    *pIntB = *pIntA;
    *pIntA = temp;

}