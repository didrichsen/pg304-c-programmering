#include "include/actor.h"

int DeleteActorList(ACTORS_LIST *pList){

    if(pList == NULL){
        printf("List uninitialized.\r\n");
        return ERROR;
    }

    ACTOR *pCurrent = pList->pHead;
    ACTOR *pTemp;

    while (pCurrent != NULL){
        pTemp = pCurrent;
        pCurrent = pCurrent->pNext;

        if(pTemp->pszFirstName != NULL){
            free(pTemp->pszFirstName);
        }
        if(pTemp->pszLastName != NULL){
            free(pTemp->pszLastName);
        }

        free(pTemp);
    }

    pList->pHead = NULL;

    return SUCCESS;

}

static ACTOR *CreateActor(char *szFirstName, char *szLastName){

    if(szFirstName == NULL || szLastName == NULL){
        return NULL;
    }

    ACTOR *pThis = (ACTOR*) malloc(sizeof(ACTOR));

    if(pThis == NULL){
        return NULL;
    }

    pThis->pszFirstName = malloc(strlen(szFirstName) + 1);
    if(pThis->pszFirstName == NULL) {
        free(pThis);
        return NULL;
    }

    pThis->pszLastName = malloc(strlen(szLastName) + 1);
    if(pThis->pszLastName == NULL) {
        free(pThis->pszFirstName);
        free(pThis);
        return NULL;
    }

    strncpy(pThis->pszFirstName, szFirstName, strlen(szFirstName) + 1);
    strncpy(pThis->pszLastName, szLastName, strlen(szLastName) + 1);

    return pThis;
}


int AddActors(ACTORS_LIST *pList, char *szFirstName, char *szLastName){


    if(szLastName == NULL || szFirstName == NULL){
        return ERROR;
    }


    ACTOR *pThis = CreateActor(szFirstName, szLastName);

    if(pThis == NULL){
        return ERROR;
    }


    if(pList->pHead == NULL){
        pList->pHead = pThis;
        pList->pHead->pNext = NULL;
    } else {
        ACTOR *pCurrent = pList->pHead;

        while(pCurrent->pNext != NULL){
            pCurrent = pCurrent->pNext;
        }

        pCurrent->pNext = pThis;
        pThis->pNext = NULL;
    }

    return SUCCESS;
}