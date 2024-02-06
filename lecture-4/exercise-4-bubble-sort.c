#include <stdio.h>
#include <stdlib.h>

#define FALSE 0;
#define TRUE 1;

void printArray(unsigned int array[], int size);
void swap(int a, int b);

void bubbleSort(unsigned int array[], int size){

    int i = 0, j = 0, temp = 0, p = 0;

    int swapped = FALSE;

    for(i = 0; i < size - 1; i++){
        swapped = FALSE;
        for(j = 0; j < size - i - 1; j++){
            if(array[j] > array[j + 1]){
                /*
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                swapped = TRUE;
                 */

                swap(*array[j], &array[j+1]);
            }
        }
        if(!swapped){
            break;
        }
    }

    for(; p < size; p++){
        printf("%d\n",array[p]);
    }

}

void swap (int &a, int &b){

    int temp;

    int *pIntA = &a;
    int *pIntB = &b;

    temp = *pIntB;
    *pIntB = *pIntA;
    *pIntA = temp;

}

void printArray(unsigned int array[], int size){

    int i = 0;

    for(; i < size; i++){
        printf("%d\n",array[i]);
    }

}

int main (int argc, char* argv[]){

    int size = argc - 1;

    if(size < 3){
        printf("Need at least two positive integers\n");
        return 1;
    }

    unsigned int array[size];

    for(int i = 1; i <= size; i++){
        array[i-1] = atoi(argv[i]);
    }

    bubbleSort(array,size);


    return 0;

}