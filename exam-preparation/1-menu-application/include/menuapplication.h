#ifndef C_PROGRAMMERING_MENU_APPLICATION_H
#define C_PROGRAMMERING_MENU_APPLICATION_H

typedef struct _ACTOR{
    char *pszFirstName;
    char *pszLastName;
    struct _ACTOR *pNext;
}ACTOR;


typedef struct _ACTORS_LIST {

    struct _ACTOR *pHead;

}ACTORS_LIST;

typedef struct _MOVIE {

    char *szMovieTitle;
    int iReleaseYear;
    struct _ACTORS_LIST *pActors;
    struct _MOVIE *pNext;
    struct _MOVIE *pPrevious;

}MOVIE;

typedef struct _MOVIE_LIST{
    struct _MOVIE *pHead;
    struct _MOVIE *pTail;
}MOVIE_LIST;


#define BUFFER_SIZE 256
#define MAX_MOVIE_TITLE 128
#define MAX_NAME_SIZE 128

#define TRUE 0
#define FALSE 1

#define SUCCESS 0
#define ERROR 2


enum MENUOPTIONS {
    MENU_OPTION_NOT_INITIALIZED = 0,
    MENU_OPTION_ADD_MOVIE = 1,
    MENU_OPTION_REMOVE_MOVIE = 2,
    MENU_OPTION_ADD_ACTOR = 3,
    MENU_OPTION_VIEW_ALL_MOVIES = 4,
    MENU_OPTION_EXIT = 5,
};

enum MENUOPTIONS GetMenuOption();
void GetZeroTerminatedUserInput(char *pszBufferDestination, int iSize);
int InsertMovie(MOVIE_LIST *pList, char *pszTitle, int iReleaseYear);
int DeleteMovies(MOVIE_LIST *pList);
int DeleteMovieBasedOnTitle(MOVIE_LIST *pList, char *pszMovieTitle);
MOVIE *FindMovie(MOVIE_LIST *pList,char *pszMovieTitle);
int AddActors(ACTORS_LIST *pList, char *szFirstName, char *szLastName);
int DeleteActorList(ACTORS_LIST *pList);
void ViewAllMovies(MOVIE_LIST *pList);


#endif //C_PROGRAMMERING_MENU_APPLICATION_H
