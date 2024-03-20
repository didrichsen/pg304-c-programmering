/*

 Exercise 3: Sorting lists
==========================

Rewrite list.h / list.c to handle lists of this type:

typedef struct _LIST {
   struct _LIST *pNext;
   char *pszString;
} LIST;

Add a InsertSorted() function that, when inserting elements, keeps a list of strings sorted
in alphabetical order.

 */

#include "include/insertsorted.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int InsertSorted(LIST **pHead, char *pszString){

    int size = strlen(pszString) + 1;

    LIST *pThis = malloc(sizeof (LIST));

    if(pThis == NULL){
        printf("Failed to allocate memory.\n");
        return 1;
    }

    memset(pThis,0,sizeof (LIST));

    pThis->pszString = malloc(size);

    if(pThis->pszString == NULL){
        printf("Failed to allocate memory");
        return 1;
    }

    memset(pThis->pszString,0,size);

    memcpy(pThis->pszString,pszString,size);

    if(*pHead == NULL){
        *pHead = pThis;
        pThis->pNext = NULL;
        return 0;
    }

    LIST *pCurrent = *pHead;

    if(strcmp((*pHead)->pszString, pThis->pszString) > 0){
        pThis->pNext = *pHead;
        *pHead = pThis;
        return 0;
    }

    while (pCurrent != NULL){

        if(pCurrent->pNext == NULL){
            pCurrent->pNext = pThis;
            pThis->pNext = NULL;
            break;
        }

        int iCompareResult = strcmp(pCurrent->pNext->pszString,pThis->pszString);

        if(iCompareResult >= 0){

            LIST *pTemp = pCurrent->pNext;
            pCurrent->pNext = pThis;
            pThis->pNext = pTemp;
            break;

        } else{
            pCurrent = pCurrent->pNext;
        }

    }
    return 0;
}


