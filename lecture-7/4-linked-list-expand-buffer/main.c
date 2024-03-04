//
// Created by simen on 3/4/2024.
//

/*

char szStr[] = "This is a long string.";
LIST *pThis = malloc (sizeof(LIST)+strlen(szStr));
strcpy (pThis->cBuf, szStr);

How would you write code that uses cBuf[] to "hold" an array of 100 longs?

 */

#include "include/exercise-3-extend-buffer.h"
//#2-include "2-include/sdlogger.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


int main(int argc, char* argv[]){

    Node *myNode = NULL;
    long array[100];
    char longAsChar[20];
    int size = 0;
    int start = 30000;
    int end = RAND_MAX;

    srand(time(NULL));

    int arraySize = sizeof (array) / sizeof (long );

    //I want to fill up the array with random numbers.
    for(int k = 0; k < arraySize; k++){
        int iRandomNumber = start + rand() % (end - start +1);
        long lRandomNumber = iRandomNumber * 10;
        array[k] = lRandomNumber;
    }

    for(int i = 0; i < arraySize; i++){
        //longAsChar is being overwritten each iteration.
        size += snprintf(longAsChar,sizeof longAsChar,"%lu",array[i]);
        //I want to allocate 1 char to have a space between each long.
        size += 1;
    }

    //Here i want to see how many characters thats written to the buffer.
    printf("Number of total character written to the buffer: %d\n",size);

    //Allocation size needed to store 100 longs.
    myNode = malloc(sizeof (Node) + size * sizeof (char));

    if(myNode == NULL){
        //sderror("Failed to allocate memory.");
        printf("Failed to allocate memory.");
        return 1;
    }

    char *ptr = myNode->cBuf;

    for(int j = 0; j < arraySize; j++){
        //Now I want to write the string representation of array[j] to the cBuf.
        size = sprintf(ptr,"%lu",array[j]);
        //Move the pointer to where the string representation of array[j] ends.
        ptr += size;
        //Add a space between each long.
        *ptr = ' ';
        //Move pointer to where it should start writing next long.
        ptr += 1;
    }

    printf("Content of cBuf: %s\n",myNode->cBuf);

    free(myNode);

    return 0;
}
