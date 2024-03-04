#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

void bubbleSort(char *pChar[], int size);
void swap(char **pCharB,char **pCharA);
void printArray(char *array[], int size);

int main (int argc, char* argv[]){

    if(argc < 2){
        printf("Usage: ex6 <string1> <string2> ... <stringN>\n");
        return 1;
    }

    char **argvArray = NULL;
    int size = argc - 1;

    //Allocating number of pointers needed
    argvArray = (char **) malloc (size * sizeof (char *));

    //Copying over elements from arv to my newly created array.
    //Check my version with veileder
    for(int i = 0; i < size; i++){
        argvArray[i] = argv[i+1];
    }

    bubbleSort(&argvArray[0],size);
    printArray(&argvArray[0],size);
/*

    bubbleSort(&argv[1], argc-1);
    printArray(&argv[1],argc-1);
*/
    free(argvArray);


    return 0;

}

void bubbleSort(char *pChar[], int size){

    int i = 0, j = 0;
    int swapped = FALSE;

    for(; i < size - 1; i++){
        swapped = FALSE;
        for(; j < size - 1; j++){
            if(strcmp(pChar[j],pChar[j+1]) > 0){
                swap(&pChar[j],&pChar[j+1]);
                swapped = TRUE;
            }
        }
        if(!swapped){
            break;
        }
    }
}

    void swap(char **pCharA,char **pCharB){

        char *temp = NULL;
        temp = *pCharA;
        *pCharA = *pCharB;
        *pCharB = temp;

    }

void printArray(char *array[], int size){

    int i = 0;

    for(; i < size;i++){
        printf("%d: %s\n", i, array[i]);
    }
}

/*

 Exercise 6 - Important exam preperation !!!

Combine the techniques from exercise 4 and 5 and print out the parameters in
sorted order. Tip: Use strcmp() or stricmp() to compare the strings.
Check the man pages and/or Google. Another tip: There is no need to copy
the strings themselves from one place to another, just swap pointers...

(This exercise was previously a obligatory assignment.)

 */