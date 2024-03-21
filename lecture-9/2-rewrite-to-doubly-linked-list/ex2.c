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

    //Empty list
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

    if (pList == NULL || pToDelete == NULL) return ERROR;

    int iRc = ERROR;
    NODE *pThis = NULL;
    NODE *pPrev = NULL;

    //List is empty
    if(pList->pHead == NULL){
        return ERROR;
    }

    //Deleting only element in list
    if(pList->pHead == pToDelete && pList->pTail == pToDelete){
        pList->pHead = NULL;
        pList->pTail = NULL;
        return iRc = OK;
    }

    //Deleting head
    else if (pList->pHead == pToDelete){
        pList->pHead = pToDelete->pNext;
        pList->pHead->pPrev = NULL;
        return iRc = OK;
    }

    //Deleting tail
    else if(pList->pTail == pToDelete){
        pList->pTail = pToDelete->pPrev;
        pList->pTail->pNext = NULL;
        return iRc = OK;
    }

    //Deleting some other element
    else{
        pThis = pList->pHead;
        while (pThis != NULL){
            if(pThis == pToDelete){
                pPrev->pNext = pThis->pNext;
                pThis->pNext->pPrev = pThis->pPrev;

                iRc = OK;
                break;
            }
            pPrev = pThis;
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
