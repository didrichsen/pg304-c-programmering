#include "include/menuapplication.h"
#include "include/sdlogger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void printMenu(){

    printf("1 - Option One\n");
    printf("2 - Option Two\n");
    printf("3 - Option Three\n");
    printf("4 - Option Four\n");
    printf("5 - Exit\n");

}

int userInput(char firstOption, char lastOption){

    char cInput[10];
    int iChoice = -1;

    do {

        //Clear the buffer before each iteration.
        memset(cInput,0,sizeof (cInput));

        //We allocate 10 bytes, but we only need 3 for this menu. Choice + Zero terminator + new line
        if(fgets(cInput,sizeof (cInput),stdin) == NULL){
            printf("Error while reading input\n");
            //Continue to skip everything in while loop and start over.
            continue;
        };

        //If strst == NULL it means input was too long since it wasent room for "\n"
        if((strstr(cInput,"\n")) == NULL){

            //Empty buffer. We empty all the way until \n since there are still chars in the buffer.
            while (getchar() != '\n');

            printf("Input to long.\nOnly menu option followed by Enter.\n");

            //If we enter else if, it means the user has made an invalid input.
        } else if(cInput[0] < firstOption || cInput[0] > lastOption) {

            printf("You have to stay within menu length, %c - %c\n",firstOption,lastOption);


        }else{
                iChoice = atoi(cInput);
        }


    } while (iChoice == -1);

    return iChoice;

}

void chooseOperation(int option){

    switch (option) {
        case 1:
            printf("Started process.. 1\n");
            usleep(2000000);
            break;
        case 2:
            printf("Started process 2\n");
            break;
        case 3:
            printf("Started process 3\n");
            break;
        case 4:
            printf("Started process 3\n");
            break;
        case 5:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid option.\n");
    }

}

void *createNode(int iSize, char *psBuffer){

    Node *pThis = NULL;
    pThis = malloc(sizeof (Node) + iSize);
    if(pThis != NULL){
        memset(pThis,0,sizeof (Node) + iSize);
        memcpy(pThis->cBuff,psBuffer,iSize);
    }

    return pThis;

}

void insertNode(Node **pHead, int iSize, char *psBuffer){

    Node *pThis = createNode(iSize,psBuffer);

    if(pThis == NULL){
        sddebug("Failed to create node.");
        return;
    }

    //If there is a node there, we want to set previous before we move head pointer.
    //If head is null, then we get a segment fault.
    if((*pHead) != NULL){
        (*pHead)->pPrevious = pThis;
    }

    pThis->pNext = (*pHead);
    (*pHead) = pThis;

    printf("%s\n", (*pHead)->cBuff);

}