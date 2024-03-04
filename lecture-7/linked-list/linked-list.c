//
// Created by Simen Didrichsen on 04/03/2024.
//

/*

 Make a set of functions to manipulate linked lists of this kind and implement the
following:

- Insert in head of list.
- Add to end of list.
- Remove list element.

 */

#include "include/linked-list.h"
#include "stdlib.h"
#include "stdio.h"

void insertAtHead(NODE **pHead, int data){

    NODE *pNewHead = NULL;
    pNewHead = (NODE*) malloc(sizeof (NODE));

    if(pNewHead == NULL){
        printf("Failed to allocate memory.");
        return;
    }

    pNewHead->data = data;
    pNewHead->pNext = *pHead;
    *pHead = pNewHead;

}

void printLinkedList(NODE *head){

    NODE *current = head;
    while(current != NULL){
        printf("Data: %d\n",current->data);
        current = current->pNext;
    }

}

void insertAtTail(NODE **pHead, int data){

    NODE *newTail = (NODE*) malloc(sizeof (NODE));

    if(newTail == NULL){
        printf("Failed to allocate memory.");
        return;
    }

    newTail->data = data;
    newTail->pNext = NULL;

    if(*pHead == NULL){
        //List is empty
        *pHead = newTail;
    } else{
        //We create a temp to loop until pNext == NULL.
        NODE *temp = *pHead;

        while (temp->pNext != NULL){
            temp = temp->pNext;
        }

        //At this point we are standing at the second to last.
        temp->pNext = newTail;
    }

}

void freeNode(NODE **pHead){

    if(pHead == NULL){
        return;
    }

    NODE *pTemp = *pHead;
    *pHead = (*pHead)->pNext;
    free(pTemp);

}