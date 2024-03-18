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
    int size = strlen(psBuffer) + 1;
    printf("Size: %d\n", size);
    int iResponseCode = 0;

    iResponseCode = insertNode(&myList,size,psBuffer);

    if(iResponseCode == 1){
        printf("Fail");
    }else{
        printf("Head: %s\n",myList.pHead->cBuff);
        printf("Tail: %s\n",myList.pTail->cBuff);
    }

    iResponseCode = addNode(&myList,size,psBufferTwo);

    if(iResponseCode == 1){
        printf("Fail");
    }else{
        printf("Head: %s\n",myList.pHead->cBuff);
        printf("Tail: %s\n", myList.pTail->cBuff);
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

    Node *current = malloc(sizeof (Node));
    memset(current,0,sizeof (Node));
    while (myList.pHead != NULL){
        current = myList.pHead;
        myList.pHead = current->pNext;
        free(current);
    }

}