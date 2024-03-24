#ifndef C_PROGRAMMERING_MENU_APPLICATION_H
#define C_PROGRAMMERING_MENU_APPLICATION_H

typedef struct _Node{
    struct _Node *pNext;
    struct _Node *pPrevious;
    int id;
    char cBuff[];
}Node;

typedef struct _List{
    struct _Node *pHead;
    struct _Node *pTail;
}List;

typedef struct _MOVIE {

    char *szMovieTitle;
    int iReleaseYear;
    struct _MOVIE *pNext;
    struct _MOVIE *pPrevious;

}MOVIE;

typedef struct _MOVIE_LIST{
    struct _MOVIE *pHead;
    struct _MOVIE *pTail;
}MOVIE_LIST;

typedef struct _ACTORS_LIST {



}ACTORS_LIST;



#define BUFFER_SIZE 256
#define MAX_MOVIE_TITLE 128

#define FALSE 0;
#define TRUE 1
#define ERROR 2


#define SUCCESS 0
#define FAIL 1

#define TRUE 0;
#define FALSE 1;

enum MENUOPTIONS {
    MENU_OPTION_NOT_INITIALIZED = 0,
    MENU_OPTION_ADD_MOVIE = 1,
    MENU_OPTION_REMOVE_MOVIE = 2,
    MENU_OPTION_THREE = 3,
    MENU_OPTION_FOUR = 4,
    MENU_OPTION_EXIT = 5,
};

enum MENUOPTIONS GetMenuOption();
void GetZeroTerminatedUserInput(char *pszBufferDestination, int iSize);
int InsertMovie(MOVIE_LIST *pList, char *pszTitle, int iReleaseYear);
int DeleteMovies(MOVIE_LIST *pList);
int DeleteMovieBasedOnTitle(MOVIE_LIST *pList, char *pszMovieTitle);


#endif //C_PROGRAMMERING_MENU_APPLICATION_H
