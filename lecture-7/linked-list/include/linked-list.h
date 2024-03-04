//
// Created by Simen Didrichsen on 04/03/2024.
//

/*
 - Insert in head of list.
- Add to end of list.
- Remove list element.
 */

#ifndef PG304_C_PROGRAMMERING_LINKED_LIST_H
#define PG304_C_PROGRAMMERING_LINKED_LIST_H

typedef struct _NODE {
    struct _NODE *pNext;
    int data;
} NODE;

void insertAtHead(NODE **pHead, int data);
void printLinkedList(NODE *head);
void insertAtTail(NODE **pHead, int data);
void freeNode(NODE **pHead);

#endif //PG304_C_PROGRAMMERING_LINKED_LIST_H
