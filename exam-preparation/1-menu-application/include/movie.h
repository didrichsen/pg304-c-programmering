#ifndef MOVIE_H
#define MOVIE_H

//Custom headers
#include "actor.h"

// Define the MOVIE structure
typedef struct MOVIE {
    char *szMovieTitle;
    int iReleaseYear;
    ACTORS_LIST *pActors;
    struct MOVIE *pNext;
    struct MOVIE *pPrevious;
} MOVIE;

// Define the MOVIE_LIST structure
typedef struct MOVIE_LIST {
    MOVIE *pHead;
    MOVIE *pTail;
} MOVIE_LIST;

//Macros
#define MAX_MOVIE_TITLE 128

// Function prototypes
int InsertMovie(MOVIE_LIST *pList, char *pszTitle, int iReleaseYear);
int DeleteMovieBasedOnTitle(MOVIE_LIST *pList, char *pszMovieTitle);
MOVIE *FindMovie(MOVIE_LIST *pList, char *pszMovieTitle);
int DeleteMovies(MOVIE_LIST *pList);

#endif // MOVIE_H