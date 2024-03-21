/*

 Excercise 4: Sorting lists - a bit more challenging
===================================================

Based on excercize 3. Rewrite list.h / list.c to handle lists of this type:

#define MAX_KEY 32

typedef struct _LIST {
   struct _LIST *pNext;
   char szKey[MAX_KEY];
   char *pszValue;
   int  iValue;
} LIST;

Add code that reads any number of lines from a file on the following format:

   <key>=[<numeric value>|"<string value>"]

For example...

   college="Westerdals"
   class=2
   grade="A+"
   students=77

Use a variant of the InsertSorted() function that, when inserting elements,
keeps the list sorted and ensures that the key doesn't become too long.

Add a function Lookup() that looks up a key and returns the value.
How can you handle the two types, integer and string?

Add another function Delete() that deletes an element given the key.

Keep the list handling in one source file and the reading of the key/value
pair file in the main source file.

 */

#include "include/keyvalue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *createNode(char *pKey, char *pValue, int iValueSize){

    LIST *pThis = NULL;
    pThis = malloc(sizeof (LIST));
    int length = 0;
    if(pThis != NULL && (length = strlen(pKey)) < MAX_KEY){
        memset(pThis,0,sizeof (LIST));
        memcpy(pThis->szKey,pKey,MAX_KEY);

        if(pValue[0] == '"'){

            pThis->pszValue = malloc(iValueSize);

            if(pThis->pszValue != NULL){
                memcpy(pThis->pszValue,pValue,iValueSize);
            }

        } else{
            pThis->iValue = atoi(pValue);

        }

    } else{
        free(pThis);
        return NULL;
    }

    return pThis;

}

int InsertSorted(LIST **pHead, char *pKey, char *pValue, int iValueSize){

    LIST *pThis = createNode(pKey,pValue,iValueSize);

    if(pThis == NULL){
        printf("To long key. Key/Value pair skipped.\n");
        return 1;
    }

    if(*pHead == NULL){
        *pHead = pThis;
        pThis->pNext = NULL;
        return 0;
    }

    LIST *pCurrent = *pHead;

    if(strcmp((*pHead)->szKey, pThis->szKey) > 0){
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

        int iCompareResult = strcmp(pCurrent->pNext->szKey,pThis->szKey);

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

RETURN_VALUE LookUp(LIST **pHead,const char *pKey){

    RETURN_VALUE myResult;

    if(*pHead == NULL){
        printf("List is empty.\n");
        myResult.iIsString = -1;
        return myResult;
    }

    LIST *pCurrent = *pHead;

    while (pCurrent != NULL){
        if(strcmp(pCurrent->szKey,pKey) == 0){
            if(pCurrent->pszValue != NULL){
                myResult.iIsString = 1;
                myResult.value.pszValue = pCurrent->pszValue;
                return myResult;
            } else{
                myResult.iIsString = 0;
                myResult.value.iValue = pCurrent->iValue;
                return myResult;
            }
        } else{
            pCurrent = pCurrent->pNext;
        }
    }

    myResult.iIsString = -1;

    return myResult;

}

void printNode(LIST *pNode) {
    if (pNode == NULL) {
        printf("The node is NULL.\n");
        return;
    }

    printf("Key: %s\n", pNode->szKey);

    // Check if the value is a string or an int
    if (pNode->pszValue != NULL) {
        // The value is a string
        printf("Value: %s (string)\n", pNode->pszValue);
    } else {
        // The value is an int
        printf("Value: %d (int)\n", pNode->iValue);
    }
}



