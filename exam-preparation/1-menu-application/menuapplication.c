#include "include/menuapplication.h"
#include "include/sdlogger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char* argv[]){
/*
    List *list = (List*) malloc(sizeof (List));
    memset(list,0,sizeof (List));
    list->pHead = NULL;
    list->pTail = NULL;
    */

    Node *myNode = NULL;

    int choice = -1;

    char *psBuffer = "simen";
    int size = strlen(psBuffer) + 1;
    printf("Size: %d\n", size);

    insertNode(&myNode,size,psBuffer);

/*
    printf("Press corresponding number and ENTER to start process.\n");

    do {

        printMenu();
        choice = userInput('1','5');
        chooseOperation(choice);


    } while (choice != 5);

    return 0;
    */

    free(myNode);

}