#include "include/menuapplication.h"
#include "include/sdlogger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char* argv[]){

    List myList;
    myList.pHead = NULL;
    myList.pTail = NULL;


    int choice = -1;

    char *psBuffer = "simen";
    char *psBufferTwo = "nemis";
    char *psBufferThree = "nemik";
    int size = strlen(psBuffer) + 1;
    printf("Size: %d\n", size);
    int iResponseCode = 0;

    iResponseCode = insertNode(&myList,size,psBuffer, 1);

    if(iResponseCode == 1){
        printf("Fail");
    }else{
        printf("Head: %s\n",myList.pHead->cBuff);
        printf("Tail: %s\n",myList.pTail->cBuff);
    }

    iResponseCode = addNode(&myList,size,psBufferTwo,2);

    if(iResponseCode == 1){
        printf("Fail");
    }else{
        printf("Head: %s\n",myList.pHead->cBuff);
        printf("Tail: %s\n", myList.pTail->cBuff);
    }

    iResponseCode = insertAfter(&myList,size,psBufferThree,1,3);

    if(iResponseCode == 1){
        printf("Fail");
    }else{
        printf("Inserted after head: %s\n",myList.pHead->pNext->cBuff);
        printf("Tail: %s\n", myList.pTail->cBuff);
    }

    iResponseCode = deleteHead(&myList);

    if(iResponseCode == 1){
        printf("Failed");
    } else{
        printf("Head deleted. New head: %s\n",myList.pHead->cBuff);
    }

    iResponseCode = deleteTail(&myList);

    if(iResponseCode == 1){
        printf("Failed");
    } else{
        printf("Tail deleted. New tail: %s\n",myList.pTail->cBuff);
    }


/*
    printf("Press corresponding number and ENTER to start process.\n");

    do {

        printMenu();
        choice = userInput('1','5');
        chooseOperation(choice);


    } while (choice != 5);

    return 0;
    */

    Node *current;
    while (myList.pHead != NULL){
        current = myList.pHead;
        printf("%s\n",current->cBuff);
        myList.pHead = current->pNext;
        free(current);
    }

}