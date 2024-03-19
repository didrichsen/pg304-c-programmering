//
// Created by Simen Didrichsen on 19/03/2024.
//

#include "include/ex2.h"
#include <stdio.h>

int main(void){

    LIST myList;
    myList.pHead = NULL;
    myList.pTail = NULL;

    InsertInList(&myList,"First",6);
    InsertInList(&myList,"Second",7);
    InsertInList(&myList,"Third",5);
    AddToList(&myList,"Fourth",7);
    AddToList(&myList,"Fifth",6);

    NODE *myNode = FindNode(&myList,1);

    RemoveFromList(&myList,myNode);

    PrintList(&myList);

    deleteAll(&myList);

}
