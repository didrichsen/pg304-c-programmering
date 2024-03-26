#include "include/movie.h"

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

int ValidReleaseYear(int ReleaseYear, int rangeStart,int rangeEnd){

    if(ReleaseYear < rangeStart || ReleaseYear >= rangeEnd){
        return 1;
    }

    return 0;
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