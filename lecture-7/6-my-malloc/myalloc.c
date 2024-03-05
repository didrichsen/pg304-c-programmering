//
// Created by simen on 3/5/2024.
//

#include "include/myalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void *myAlloc(const char* pFlags, ...){

    char pType[10];
    char pFlag;
    void *p = NULL;

    va_list vaArgumentPointer;

    sscanf(pFlags,"%s %c", pType, &pFlag);

    va_start(vaArgumentPointer, pFlags);

    int iNumberOfElements = va_arg(vaArgumentPointer, int);

    if (strcmp(pType, "int") == 0) {
        p = malloc(sizeof(int) * iNumberOfElements);
        if(p != NULL) {
            if (pFlag == 'T') {
                int value = va_arg(vaArgumentPointer,int );
                int *intArray = (int*)(p);
                for(int i = 0; i < iNumberOfElements; i++){
                    intArray[i] = value;
                }
            } else {
                memset(p, 0, iNumberOfElements * sizeof(int));
            }
        }
    } else if (strcmp(pType, "float") == 0) {
        p = malloc(sizeof(float) * iNumberOfElements);
        if(p != NULL){
            if(pFlag == 'T'){
                double dValue = va_arg(vaArgumentPointer,double);
                float floatValue = (float ) dValue;
                float *fArray = (float* )(p);
                for(int j = 0; j < iNumberOfElements; j++){
                    fArray[j] = floatValue;
                }
            } else{
                memset(p,0,iNumberOfElements * sizeof (float ));
            }
        }
    } else if (strcmp(pType, "char") == 0) {
        p = malloc(sizeof(char) * iNumberOfElements);
        if(p != NULL){
            if(pFlag == 'T'){
                int iValue = va_arg(vaArgumentPointer,int );
                char cValue = (char ) iValue;
                memset(p,cValue,iNumberOfElements * sizeof (char ));
            } else {
                memset(p,0,iNumberOfElements * sizeof (char ));
            }
        }
    }

    va_end(vaArgumentPointer);

    return p;

}
