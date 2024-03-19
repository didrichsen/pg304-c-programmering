//
// Created by Simen Didrichsen on 19/03/2024.
//

#ifndef PG304_C_PROGRAMMERING_EX2_H
#define PG304_C_PROGRAMMERING_EX2_H

#define OK      0
#define ERROR   1

typedef unsigned char BYTE;

typedef struct _NODE {
    struct _NODE *pNext;
    struct _NODE *pPrev;
    int iSze;
    BYTE byBuf[];
} NODE;

typedef struct _LIST {
    NODE *pHead;
    NODE *pTail;
} LIST;

int InsertInList (LIST *pList, void *pvData, int iSze);
void PrintList (LIST *pThis);
int deleteAll(LIST *pList);
int AddToList (LIST *pList, void *pvData, int iSze);
int RemoveFromList (LIST *pList, NODE *pToDelete);
NODE *FindNode(LIST *pList, int place);

#endif //PG304_C_PROGRAMMERING_EX2_H
