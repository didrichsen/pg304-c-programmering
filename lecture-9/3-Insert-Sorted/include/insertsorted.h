//
// Created by Simen Didrichsen on 20/03/2024.
//

#ifndef PG304_C_PROGRAMMERING_INSERTSORTED_H
#define PG304_C_PROGRAMMERING_INSERTSORTED_H

typedef struct _LIST {
    struct _LIST *pNext;
    char *pszString;
} LIST;

int InsertSorted(LIST **pHead, char *pszString);

#endif //PG304_C_PROGRAMMERING_INSERTSORTED_H
