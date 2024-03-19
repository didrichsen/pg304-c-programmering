/*

 Exercise 2: Doubly linked lists
===============================

Look at List/lish.h and list.c. Rewrite the list to be a doubly linked list.
For the list-head and tail use the following struct:

typedef struct _LISTHEAD {
   LIST *pHead;
   LIST *pTail;
} LISTHEAD;

Rewrite the Insert/Append/Delete-functions to use a LISTHEAD * as first parameter.
Rewrite testlist.c to handle the new format.

 */

#include "include/ex2.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static NODE *CreateNode (void *pvData, int iSze)
{
    NODE *pThis = malloc (sizeof(NODE) + iSze);
    if (pThis != NULL) {
        memset (pThis, 0, sizeof(NODE) + iSze);
        pThis->iSze = iSze;
        memcpy (pThis->byBuf, pvData, iSze);
    }
    return pThis;
}

int InsertInList (LIST *pList, void *pvData, int iSze)
{
    int iRc = ERROR;
    NODE *pThis = CreateNode (pvData, iSze);

    if(pThis == NULL){
        return iRc;
    }

    if(pList->pHead == NULL){
        pList->pHead = pThis;
        pList->pTail = pThis;
        pThis->pNext = NULL;
        pThis->pPrev = NULL;
    } else {
        pThis->pNext = pList->pHead;
        pList->pHead->pPrev = pThis;
        pList->pHead = pThis;
        pThis->pPrev = NULL;
    }

    return iRc = OK;
}

void PrintList (LIST *pThis)
{

    NODE *pCurrent = pThis->pHead;
    int i = 0;

    while (pCurrent != NULL){
        printf("%d: %s\n",++i, pCurrent->byBuf);
        pCurrent = pCurrent->pNext;
    }

}

int deleteAll(LIST *pList){

    int iRc = ERROR;

    if(pList == NULL){
        return iRc;
    }

    NODE *pCurrent = pList->pHead;
    NODE *pTemp;

    while (pCurrent != NULL){
        pTemp = pCurrent;
        pCurrent = pCurrent->pNext;
        free(pTemp);
    }

    pList->pHead = NULL;
    pList->pTail = NULL;

    return iRc = OK;

}

int AddToList (LIST *pList, void *pvData, int iSze)
{
    int iRc = ERROR;

    if(pList == NULL){
        return iRc;
    }

    NODE *pThis = CreateNode (pvData, iSze);

    if(pThis == NULL){
        return iRc;
    }

    if(pList->pTail == NULL){
        pList->pHead = pThis;
        pList->pTail = pThis;
    } else {
        pThis->pPrev = pList->pTail;
        pList->pTail->pNext = pThis;
        pList->pTail = pThis;
    }

    return iRc = OK;
}

int RemoveFromList (LIST *pList, NODE *pToDelete)
{
    int iRc = ERROR;
    NODE *pThis = NULL;

    if (pList->pHead == pToDelete) {
        if(pList->pHead->pNext == NULL){
            pList->pTail = NULL;
        }
        pList->pHead = pToDelete->pNext;
        iRc = OK;
    } else{
        pThis = pList->pHead;
        while (pThis != NULL){
            if(pThis->pNext == pToDelete){
                pThis->pNext = pToDelete->pNext;
                pToDelete->pNext->pPrev = pThis;

                iRc = OK;
                break;
            }
            pThis = pThis->pNext;
        }
    }

    if (iRc == OK) free (pToDelete);
    return iRc;
}

NODE *FindNode(LIST *pList, int place){

    NODE *pCurrent = pList->pHead;
    for(int i = 1; i < place; i++){
        pCurrent = pCurrent->pNext;
    }

    return pCurrent;

}
