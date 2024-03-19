#include "include/menuapplication.h"
#include "include/sdlogger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void printMenu(){

    printf("1 - Option One\n");
    printf("2 - Option Two\n");
    printf("3 - Option Three\n");
    printf("4 - Option Four\n");
    printf("5 - Exit\n");

}

int userInput(char firstOption, char lastOption){

    char cInput[10];
    int iChoice = -1;

    do {

        //Clear the buffer before each iteration.
        memset(cInput,0,sizeof (cInput));

        //We allocate 10 bytes, but we only need 3 for this menu. Choice + Zero terminator + new line
        if(fgets(cInput,sizeof (cInput),stdin) == NULL){
            printf("Error while reading input\n");
            //Continue to skip everything in while loop and start over.
            continue;
        };

        //If strst == NULL it means input was too long since it wasent room for "\n"
        if((strstr(cInput,"\n")) == NULL){

            //Empty buffer. We empty all the way until \n since there are still chars in the buffer.
            while (getchar() != '\n');

            printf("Input to long.\nOnly menu option followed by Enter.\n");

            //If we enter else if, it means the user has made an invalid input.
        } else if(cInput[0] < firstOption || cInput[0] > lastOption) {

            printf("You have to stay within menu length, %c - %c\n",firstOption,lastOption);


        }else{
                iChoice = atoi(cInput);
        }


    } while (iChoice == -1);

    return iChoice;

}

void chooseOperation(int option){

    switch (option) {
        case 1:
            printf("Started process.. 1\n");
            usleep(2000000);
            break;
        case 2:
            printf("Started process 2\n");
            break;
        case 3:
            printf("Started process 3\n");
            break;
        case 4:
            printf("Started process 3\n");
            break;
        case 5:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid option.\n");
    }

}

void *createNode(int iSize, char *psBuffer, int id){

    Node *pThis = NULL;
    pThis = malloc(sizeof (Node) + iSize);
    if(pThis != NULL){
        memset(pThis,0,sizeof (Node) + iSize);
        memcpy(pThis->cBuff,psBuffer,iSize);
        pThis->id = id;
    }

    return pThis;

}

//Adds node to head
int insertNode(List *pList, int iSize, char *psBuffer, int id){

    Node *pThis = createNode(iSize,psBuffer,id);

    if(pThis == NULL){
        //sddebug("Failed to create node.");
        return FAIL;
    }

    //List is empty
    if(pList->pHead == NULL){
        pThis->pNext = NULL;
        pThis->pPrevious = NULL;
        pList->pHead = pThis;
        pList->pTail = pThis;

        //List has existing nodes
    } else{
        pThis->pNext = pList->pHead;
        pList->pHead->pPrevious = pThis;
        pList->pHead = pThis;
        pThis->pPrevious = NULL;
    }

    return SUCCESS;

}

//Adds node to tail
int addNode(List *pList, int iSize, char *psBuffer, int id){

    Node *pThis = createNode(iSize,psBuffer,id);

    if(pThis == NULL){
        //sddebug("Failed to create node.");
        return FAIL;
    }

    if(pList->pTail == NULL){
        pThis->pNext = NULL;
        pThis->pPrevious = NULL;
        pList->pHead = pThis;
        pList->pTail = pThis;
    } else{
        pList->pTail->pNext = pThis;
        pThis->pPrevious = pList->pTail;
        pThis->pNext = NULL;
        pList->pTail = pThis;
    }

    return SUCCESS;
}

//Add to location
int insertAfter(List *pList, int iSize, char *psBuffer, int insertAfterId, int id){

    Node *pThis = createNode(iSize,psBuffer,id);

    if(pThis == NULL){
        //sddebug("Failed to create node.");
        return FAIL;
    }

    Node *pCurrent = pList->pHead;

    while (pCurrent != NULL){
        if(pCurrent->id == insertAfterId){
            pThis->pNext = pCurrent->pNext;
            pThis->pPrevious = pCurrent;

            if(pCurrent->pNext != NULL){
                pCurrent->pNext->pPrevious = pThis;
            } else{
                //Hvis current.next == NULL så vil pThis være siste node.
                pList->pTail = pThis;
            }

            pCurrent->pNext = pThis;

            return SUCCESS;
        }

        pCurrent = pCurrent->pNext;
    }

    //We didnt find the node to insert after
    free(pThis);
    return FAIL;
}

//Deletes head of list.
int deleteHead(List *pList){

    if(pList == NULL || pList->pHead == NULL){
        return FAIL;
    }

    Node *current = pList->pHead;

    if(current->pNext != NULL) {
        current->pNext->pPrevious = NULL;
    } else {
        //It was the last node in list.
        pList->pTail = NULL;
    }

    pList->pHead = current->pNext;

    free(current);

    return SUCCESS;

}

//Deletes tail
int deleteTail(List *pList){

    if(pList == NULL || pList->pTail == NULL){
        return FAIL;
    }

    Node *current = pList->pTail;

    if(current->pPrevious != NULL) {
        current->pPrevious->pNext = NULL;
    } else {
        //We need to update pointer since there was only one node in the list, or else dangling pointer.
        pList->pHead = NULL;
    }

    pList->pTail = current->pPrevious;

    free(current);

    return SUCCESS;

}