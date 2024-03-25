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
    printf("> 3 -\tAdd Actor to Movie\r\n");
    printf("> 4 -\tView all Movies\r\n");
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
        return MENU_OPTION_ADD_ACTOR;
    } else if(option == 4){
        return MENU_OPTION_VIEW_ALL_MOVIES;
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

    pThis->pActors = (ACTORS_LIST*) malloc(sizeof (ACTORS_LIST));

    if(pThis->pActors == NULL){
        free(pThis->szMovieTitle);
        free(pThis);
        return NULL;
    }
    pThis->pActors->pHead = NULL;
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

            DeleteActorList(pCurrent->pActors);
            free(pCurrent->szMovieTitle);
            free(pCurrent);

            return SUCCESS;

        }
        pCurrent = pCurrent->pNext;
    }

    return ERROR;

}

MOVIE *FindMovie(MOVIE_LIST *pList,char *pszMovieTitle){

    if(pList == NULL || pszMovieTitle == NULL){
        return NULL;
    }

    MOVIE *pMovie = pList->pHead;
    while (pMovie != NULL){
        if(strcmp(pMovie->szMovieTitle,pszMovieTitle) == 0){
            return pMovie;
        }
        pMovie = pMovie->pNext;
    }

    return NULL;

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

        DeleteActorList(pTemp->pActors);

        free(pTemp);
    }

    pList->pHead = NULL;
    pList->pTail = NULL;

    return SUCCESS;

}

int DeleteActorList(ACTORS_LIST *pList){

    if(pList == NULL){
        printf("List uninitialized.\r\n");
        return ERROR;
    }

    ACTOR *pCurrent = pList->pHead;
    ACTOR *pTemp;

    while (pCurrent != NULL){
        pTemp = pCurrent;
        pCurrent = pCurrent->pNext;

        if(pTemp->pszFirstName != NULL){
            free(pTemp->pszFirstName);
        }
        if(pTemp->pszLastName != NULL){
            free(pTemp->pszLastName);
        }

        free(pTemp);
    }

    pList->pHead = NULL;

    return SUCCESS;

}

static ACTOR *CreateActor(char *szFirstName, char *szLastName){

    if(szFirstName == NULL || szLastName == NULL){
        return NULL;
    }

    ACTOR *pThis = (ACTOR*) malloc(sizeof(ACTOR));

    if(pThis == NULL){
        return NULL;
    }

    pThis->pszFirstName = malloc(strlen(szFirstName) + 1);
    if(pThis->pszFirstName == NULL) {
        free(pThis);
        return NULL;
    }

    pThis->pszLastName = malloc(strlen(szLastName) + 1);
    if(pThis->pszLastName == NULL) {
        free(pThis->pszFirstName);
        free(pThis);
        return NULL;
    }

    strncpy(pThis->pszFirstName, szFirstName, strlen(szFirstName) + 1);
    strncpy(pThis->pszLastName, szLastName, strlen(szLastName) + 1);

    return pThis;
}


int AddActors(ACTORS_LIST *pList, char *szFirstName, char *szLastName){


    if(szLastName == NULL || szFirstName == NULL){
        return ERROR;
    }


    ACTOR *pThis = CreateActor(szFirstName, szLastName);

    if(pThis == NULL){
        return ERROR;
    }


    if(pList->pHead == NULL){
        pList->pHead = pThis;
        pList->pHead->pNext = NULL;
    } else {
        ACTOR *pCurrent = pList->pHead;

        while(pCurrent->pNext != NULL){
            pCurrent = pCurrent->pNext;
        }

        pCurrent->pNext = pThis;
        pThis->pNext = NULL;
    }

    return SUCCESS;
}

void ViewAllMovies(MOVIE_LIST *pList){

    if(pList == NULL || pList->pHead == NULL){
        printf("No movies to show\r\n");
        return;
    }

    MOVIE *pCurrent = pList->pHead;
    int iCounter = 1;

    while (pCurrent != NULL){

        printf("Movie, %d:\r\n", iCounter);
        printf("Title: %s\r\n", pCurrent->szMovieTitle);
        printf("Release Year: %d\r\n", pCurrent->iReleaseYear);
        if(pCurrent->pActors != NULL){
            ACTOR *pCurrentActor = pCurrent->pActors->pHead;
            int iCounterActor = 1;
            while (pCurrentActor != NULL){
                printf("Actor %d : %s, %s\r\n",iCounterActor,pCurrentActor->pszFirstName,pCurrentActor->pszLastName);
                pCurrentActor = pCurrentActor->pNext;
                iCounterActor++;
            }
        } else{
            printf("No actors listed for this movie.\r\n");
        }
        pCurrent = pCurrent->pNext;
        iCounter++;
        printf("\r\n");
    }

}


