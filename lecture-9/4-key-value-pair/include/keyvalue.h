//
// Created by Simen Didrichsen on 20/03/2024.
//

#ifndef PG304_C_PROGRAMMERING_KEYVALUE_H
#define PG304_C_PROGRAMMERING_KEYVALUE_H

#define MAX_KEY 32
#define BUFFFERSZE 256

typedef struct _LIST {
    struct _LIST *pNext;
    char szKey[MAX_KEY];
    char *pszValue;
    int  iValue;
} LIST;

typedef struct _RETURN_VALUE {
    int iIsString;
    union {
        char *pszValue;
        int iValue;
    } value;
} RETURN_VALUE;

typedef struct _RETURN_OBJECT{
    char *pszValue;
    int iValue;
} RETURN_OBJECT;

void *createNode(char *pKey, char *pValue, int iValueSize);
void printNode(LIST *pNode);
int InsertSorted(LIST **pHead, char *pKey, char *pValue, int iValueSize);
RETURN_OBJECT *LookUp(LIST **pHead,const char *pKey, RETURN_OBJECT *resultObject);

#endif //PG304_C_PROGRAMMERING_KEYVALUE_H
