#include "include/insertsorted.h"
#include <stdio.h>
#include <stdlib.h>

int main (void){

    LIST *pHead = NULL;

    InsertSorted(&pHead,"B");
    InsertSorted(&pHead,"C");
    InsertSorted(&pHead,"A");
    InsertSorted(&pHead,"R");
    InsertSorted(&pHead,"S");
    InsertSorted(&pHead,"T");
    InsertSorted(&pHead,"D");

    LIST *pCurrent = pHead;
    LIST *pTemp;

    while (pCurrent != NULL){
        pTemp = pCurrent;
        printf("%s\n", pTemp->pszString);
        pCurrent = pCurrent->pNext;
        free(pTemp);
    }


    return 0;
}