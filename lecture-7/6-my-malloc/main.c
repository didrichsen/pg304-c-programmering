//
// Created by simen on 3/5/2024.
//

#include "include/myalloc.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){

    //Float call
    float *pFloat = NULL;

    pFloat =(float*) myAlloc("float T",10,235.0);

    if(pFloat == NULL){
        printf("Failed to allocate.");
    } else {
        for(int i = 0; i < 10; i++){
            printf("%f\n", pFloat[i]);
        }
    }

    free(pFloat);

    //Int call
    int *pInt = NULL;

    pInt = (int*) myAlloc("int T",10,235);

    if(pInt == NULL){
        printf("Failed to allocate.");
    }else{
        for(int j = 0; j < 10; j++){
            printf("%d\n", pInt[j]);
        }
    }

    free(pInt);

    //Char call
    char *pChar = NULL;

    pChar = (char*) myAlloc("char T",10,'A');

    if(pChar == NULL){
        printf("Failed to allocate memory.");
    } else {
        for(int k = 0; k < 10; k++){
            printf("%c\n",pChar[k]);
        }
    }


    return 0;
}
