#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "include/menuapplication.h"
#include "include/sdlogger.h"

//Prints menu.
static void PrintMenu() {

    printf("\x1b[1;36m");
    printf("*************************\r\n");
    printf("*       MAIN MENU       *\r\n");
    printf("*************************\r\n");
    printf("\r\nPlease select an option:\r\n");
    printf("> 1 -\tAdd Movie\r\n");
    printf("> 2 -\tRemove Movie\r\n");
    printf("> 3 -\tOption Three\r\n");
    printf("> 4 -\tOption Four\r\n");
    printf("> 5 -\tExit\r\n");
    printf("*************************\r\n");
    printf("\x1b[0m");

}

//Removes spaces, newline char and forces zero terminator to be the last char.
static void SanitizeInput (char *psText){

    char *d;
    char *end;
    long length;

    d = psText;

    //Whitespace in front
    //Move until I hit first character
    while (*d == ' '){
        ++d;
    }

    end = d;
    //Move end to newline character
    while (*end != '\0' && *end != '\n'){
        ++end;
    }

    if(*end == '\n'){
        *end = '\0';
    }

    //Moving end back from zero terminator
    end--;

    //Moving it back until it hits the last character
    while (end > d && *end == ' '){
        --end;
    }

    //Adding zero terminator
    *(end + 1) = '\0';

    //The pointer arithmetic doesn't include the last pointer when calculating addresses, so I have to add 1.
    length = end - d + 1;

    //Using memmove since im copying from same memory space. Safer than memcopy.
    //I add +1 to account for \0
    memmove(psText,d,length + 1);

}

//Returns a zero terminated string not longer than iSize.
void GetZeroTerminatedUserInput(char *pszBufferDestination, int iSize){

    char szLocalBuffer[BUFFER_SIZE] = {0};
    int iInputValid = FALSE;

    do {

        iInputValid = TRUE;

        fgets(szLocalBuffer,BUFFER_SIZE-1, stdin);

        //If strstr returns NULL it means input was too long since it wasent room for "\n"
        if((strstr(szLocalBuffer,"\n")) == NULL || strlen(szLocalBuffer) > iSize) {

            printf("Input to long.\r\n");
            //Empty buffer. We empty all the way until \n since there are still chars in the buffer.
            while (getchar() != '\n');

            iInputValid = FALSE;
        }

    } while (iInputValid);

    SanitizeInput(szLocalBuffer);

    strncpy(pszBufferDestination,szLocalBuffer,iSize);

}

//Makes use of GetZeroTerminatedUserInput but also do a couple of checks that specific to menu option.
static int GetMenuInput(char firstOption, char lastOption){

    char cInput[10] = {0};
    int iChoice = -1;

    PrintMenu();

    do {

        GetZeroTerminatedUserInput(cInput,10);

        //We check [0] which should be within range in the ASCII Table.
        //If [1] is not \0 then the user has inputted higher number than 10.
        if(cInput[0] < firstOption || cInput[0] > lastOption || cInput[1] != '\0') {

            printf("You have to stay within menu length, %c - %c\r\n",firstOption,lastOption);

        }else{

                iChoice = atoi(cInput);

        }

    } while (iChoice == -1);

    return iChoice;

}

//Checks the option return from GetMenuInput and return the corresponding enum value.
enum MENUOPTIONS GetMenuOption(){

    int option = GetMenuInput('1','5');

    if(option == 1){
        return MENU_OPTION_ADD_MOVIE;
    } else if(option == 2){
        return MENU_OPTION_REMOVE_MOVIE;
    } else if(option == 3){
        return MENU_OPTION_THREE;
    } else if(option == 4){
        return MENU_OPTION_FOUR;
    } else if(option == 5){
        return MENU_OPTION_EXIT;
    } else {
        return MENU_OPTION_NOT_INITIALIZED;
    }
}

//Creating a movie that later can be placed into a doubly linked list.
static void *CreateMovie(char *pszTitle, int iReleaseYear){

    if(pszTitle == NULL){
        return NULL;
    }

    MOVIE *pThis = (MOVIE *) malloc(sizeof (MOVIE));

    if(pThis == NULL){
        return NULL;
    }

    memset(pThis,0,sizeof (MOVIE));

    pThis->iReleaseYear = iReleaseYear;

    pThis->szMovieTitle = malloc(strlen(pszTitle) + 1);

    if(pThis->szMovieTitle == NULL){
        free(pThis);
        return NULL;
    }

    strncpy(pThis->szMovieTitle,pszTitle, strlen(pszTitle));
    //Since we here are working on index I can use strlen to place \0 at the last index.
    pThis->szMovieTitle[strlen(pszTitle)] = '\0';

    return pThis;

}

//Inserting a movie at the head of the doubly linked list.
int InsertMovie(MOVIE_LIST *pList, char *pszTitle, int iReleaseYear){

    MOVIE *pThis = CreateMovie(pszTitle, iReleaseYear);

    if(pThis == NULL){
        //sddebug("Failed to create node.");
        return ERROR;
    }

    //List is empty
    if(pList->pHead == NULL){
        pThis->pNext = NULL;
        pThis->pPrevious = NULL;
        pList->pHead = pThis;
        pList->pTail = pThis;

        //List has existing movies
    } else{
        pThis->pNext = pList->pHead;
        pList->pHead->pPrevious = pThis;
        pList->pHead = pThis;
        pThis->pPrevious = NULL;
    }

    return SUCCESS;

}

//Delete movie based on title.
int DeleteMovieBasedOnTitle(MOVIE_LIST *pList, char *pszMovieTitle){

    //Checking if list in not existing or if list are empty.
    if(pList == NULL || pList->pHead == NULL){
        return ERROR;
    }

    MOVIE *pCurrent = pList->pHead;

    while (pCurrent != NULL){
        if(strcmp(pCurrent->szMovieTitle,pszMovieTitle) == 0){

            //Deleting head
            if(pCurrent->pPrevious == NULL){
                if(pCurrent->pNext == NULL){
                    //pCurrent is the only movie in the list.
                    pList->pTail = NULL;
                    pList->pHead = NULL;
                }  else {
                    pCurrent->pNext->pPrevious = NULL;
                    pList->pHead = pCurrent->pNext;
                }
            }
            //Deleting tail
            else if (pCurrent->pNext == NULL){
                pCurrent->pPrevious->pNext = NULL;
                pList->pTail = pCurrent->pPrevious;
            }

            //Deleting somewhere in the middle
            else{
                pCurrent->pPrevious->pNext = pCurrent->pNext;
                pCurrent->pNext->pPrevious = pCurrent->pPrevious;
            }

            free(pCurrent->szMovieTitle);
            free(pCurrent);

            return SUCCESS;

        }
        pCurrent = pCurrent->pNext;
    }

    return ERROR;

}

//Deletes all movies in list.
int DeleteMovies(MOVIE_LIST *pList){

    if(pList == NULL){
        return ERROR;
    }

    MOVIE *pCurrent = pList->pHead;
    MOVIE *pTemp;

    while (pCurrent != NULL){
        pTemp = pCurrent;
        pCurrent = pCurrent->pNext;
        if(pTemp->szMovieTitle != NULL){
            free(pTemp->szMovieTitle);
        }
        free(pTemp);
    }

    pList->pHead = NULL;
    pList->pTail = NULL;

    return SUCCESS;

}

void *createNode(int iSize, char *psBuffer, int id){

    Node *pThis = NULL;
    pThis = malloc(sizeof (Node) + iSize);
    if(pThis != NULL){
        memset(pThis,0,sizeof (Node) + iSize);
        memcpy(pThis->cBuff,psBuffer,iSize);
        pThis->id = id;
    }

    return pThis;

}

//Adds node to head
int insertNode(List *pList, int iSize, char *psBuffer, int id){

    Node *pThis = createNode(iSize,psBuffer,id);

    if(pThis == NULL){
        //sddebug("Failed to create node.");
        return FAIL;
    }

    //List is empty
    if(pList->pHead == NULL){
        pThis->pNext = NULL;
        pThis->pPrevious = NULL;
        pList->pHead = pThis;
        pList->pTail = pThis;

        //List has existing nodes
    } else{
        pThis->pNext = pList->pHead;
        pList->pHead->pPrevious = pThis;
        pList->pHead = pThis;
        pThis->pPrevious = NULL;
    }

    return SUCCESS;

}

//Adds node to tail
int addNode(List *pList, int iSize, char *psBuffer, int id){

    Node *pThis = createNode(iSize,psBuffer,id);

    if(pThis == NULL){
        //sddebug("Failed to create node.");
        return FAIL;
    }

    if(pList->pTail == NULL){
        pThis->pNext = NULL;
        pThis->pPrevious = NULL;
        pList->pHead = pThis;
        pList->pTail = pThis;
    } else{
        pList->pTail->pNext = pThis;
        pThis->pPrevious = pList->pTail;
        pThis->pNext = NULL;
        pList->pTail = pThis;
    }

    return SUCCESS;
}

//Add to location
int insertAfter(List *pList, int iSize, char *psBuffer, int insertAfterId, int id){

    Node *pThis = createNode(iSize,psBuffer,id);

    if(pThis == NULL){
        //sddebug("Failed to create node.");
        return FAIL;
    }

    Node *pCurrent = pList->pHead;

    while (pCurrent != NULL){
        if(pCurrent->id == insertAfterId){
            pThis->pNext = pCurrent->pNext;
            pThis->pPrevious = pCurrent;

            if(pCurrent->pNext != NULL){
                pCurrent->pNext->pPrevious = pThis;
            } else{
                //Hvis current.next == NULL så vil pThis være siste node.
                pList->pTail = pThis;
            }

            pCurrent->pNext = pThis;

            return SUCCESS;
        }

        pCurrent = pCurrent->pNext;
    }

    //We didnt find the node to insert after
    free(pThis);
    return FAIL;
}

//Deletes head of list.
int deleteHead(List *pList){

    if(pList == NULL || pList->pHead == NULL){
        return FAIL;
    }

    Node *current = pList->pHead;

    if(current->pNext != NULL) {
        current->pNext->pPrevious = NULL;
    } else {
        //It was the last node in list.
        pList->pTail = NULL;
    }

    pList->pHead = current->pNext;

    free(current);

    return SUCCESS;

}

//Deletes tail
int deleteTail(List *pList){

    if(pList == NULL || pList->pTail == NULL){
        return FAIL;
    }

    Node *current = pList->pTail;

    if(current->pPrevious != NULL) {
        current->pPrevious->pNext = NULL;
    } else {
        //We need to update pointer since there was only one node in the list, or else dangling pointer.
        pList->pHead = NULL;
    }

    pList->pTail = current->pPrevious;

    free(current);

    return SUCCESS;

}

int deleteBasedOnID(List *pList, int id){

    if(pList == NULL || pList->pHead == NULL){
        return FAIL;
    }

    Node *current = pList->pHead;

    while (current != NULL){
        if(current->id == id){

            if(current->pPrevious == NULL){
                pList->pHead = current->pNext;
                if(current->pNext != NULL){
                    current->pNext->pPrevious = NULL;
                } else{
                    //If we are here. This was the only node and we need to update tail.
                    //Head will at this point already be NULL.
                    pList->pTail = NULL;
                }
            } else {
                current->pPrevious->pNext = current->pNext;

                if(current->pNext != NULL){
                    current->pNext->pPrevious = current->pPrevious;
                } else{
                    //If the current is the last node in the list
                    pList->pTail = current->pPrevious;
                }
            }

            free(current);

            return SUCCESS;

        }
        current = current->pNext;
    }

    return FAIL;

}

int deleteAll(List *pList){

    if(pList == NULL){
        return FAIL;
    }

    Node *pCurrent = pList->pHead;
    Node *pTemp;

    while (pCurrent != NULL){
        pTemp = pCurrent;
        pCurrent = pCurrent->pNext;
        free(pTemp);
    }

    pList->pHead = NULL;
    pList->pTail = NULL;

    return SUCCESS;

}

Node *findNode(List *pList, int id){

    if(pList == NULL){
        return NULL;
    }

    Node *pCurrent = pList->pHead;

    while (pCurrent != NULL){
        if(pCurrent->id == id){
            return pCurrent;
        }

        pCurrent = pCurrent->pNext;
    }

    return NULL;
}

int swapNodes(List *pList, Node *nodeOne, Node *nodeTwo){

    if(pList == NULL || nodeOne == NULL || nodeTwo == NULL || nodeOne == nodeTwo){
        return FAIL;
    }


    if(nodeOne->pNext == nodeTwo){ // nodeOne is immediately before nodeTwo
        nodeOne->pNext = nodeTwo->pNext;
        nodeTwo->pPrevious = nodeOne->pPrevious;

        if(nodeOne->pPrevious != NULL){
            nodeOne->pPrevious->pNext = nodeTwo;
        }
        if(nodeTwo->pNext != NULL){
            nodeTwo->pNext->pPrevious = nodeOne;
        }

        nodeTwo->pNext = nodeOne;
        nodeOne->pPrevious = nodeTwo;
    } else if(nodeTwo->pNext == nodeOne){ // nodeTwo is immediately before nodeOne
        nodeTwo->pNext = nodeOne->pNext;
        nodeOne->pPrevious = nodeTwo->pPrevious;

        if(nodeTwo->pPrevious != NULL){
            nodeTwo->pPrevious->pNext = nodeOne;
        }
        if(nodeOne->pNext != NULL){
            nodeOne->pNext->pPrevious = nodeTwo;
        }

        nodeOne->pNext = nodeTwo;
        nodeTwo->pPrevious = nodeOne;
    } else { // Nodes are not next to each other
        Node *temp = nodeOne->pNext;
        nodeOne->pNext = nodeTwo->pNext;
        nodeTwo->pNext = temp;

        temp = nodeOne->pPrevious;
        nodeOne->pPrevious = nodeTwo->pPrevious;
        nodeTwo->pPrevious = temp;

        if(nodeOne->pNext != NULL){
            nodeOne->pNext->pPrevious = nodeOne;
        }
        if(nodeTwo->pNext != NULL){
            nodeTwo->pNext->pPrevious = nodeTwo;
        }
        if(nodeOne->pPrevious != NULL){
            nodeOne->pPrevious->pNext = nodeOne;
        }
        if(nodeTwo->pPrevious != NULL){
            nodeTwo->pPrevious->pNext = nodeTwo;
        }
    }

    // Update the head and tail if needed
    if(pList->pHead == nodeOne){
        pList->pHead = nodeTwo;
    } else if(pList->pHead == nodeTwo){
        pList->pHead = nodeOne;
    }

    if(pList->pTail == nodeOne){
        pList->pTail = nodeTwo;
    } else if(pList->pTail == nodeTwo){
        pList->pTail = nodeOne;
    }

    return SUCCESS;
}

void printList(List *pList){

    if(pList == NULL){
        printf("List pointer is NULL.\n");
        return;
    }

    if(pList->pHead == NULL){
        printf("List is empty.\n");
        return;
    }

    Node *pCurrent = pList->pHead;
    while(pCurrent != NULL){
        printf("%s\n", pCurrent->cBuff);
        pCurrent = pCurrent->pNext;
    }
    printf("-----------------------------------\n");
}