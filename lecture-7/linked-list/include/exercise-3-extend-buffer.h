//
// Created by simen on 3/4/2024.
//

#ifndef C_PROGRAMMERING_LINKED_LIST_H
#define C_PROGRAMMERING_LINKED_LIST_H

typedef struct _Node {
    struct Node *pNext;
    int iSze;
    char cBuf[1];
} Node;

int countDigits(long number);

#endif //C_PROGRAMMERING_LINKED_LIST_H
