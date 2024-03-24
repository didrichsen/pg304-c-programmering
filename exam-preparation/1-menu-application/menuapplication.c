#include "include/menuapplication.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void ToMainMenu();

int main(int argc, char* argv[]) {

    //Used in switch case to determine operation.
    enum MENUOPTIONS eMenuOption;
    //Movie list keeps track of head and tail
    MOVIE_LIST movieList;
    movieList.pHead = NULL;
    movieList.pTail = NULL;
    //Used to store title of movie, MAX_MOVIE_TITLE 128 characters.
    char szMovieTitle[MAX_MOVIE_TITLE] = {0};
    //Buffer used for different user interactions. BUFFER_SIZE 256 characters.
    char pszBuffer[BUFFER_SIZE] = {0};
    //Movie release year
    int iReleaseYear = 0;
    //Return code to check for errors
    int iRc = 0;


    do {

        eMenuOption = GetMenuOption();

        switch (eMenuOption) {
            case MENU_OPTION_ADD_MOVIE:

                do {

                    //Everything set to null or 0
                    memset(szMovieTitle, 0, MAX_MOVIE_TITLE);
                    memset(pszBuffer, 0, BUFFER_SIZE);
                    iReleaseYear = 0;

                    //Getting the title of the movie
                    printf("Enter movie title\r\n");
                    GetZeroTerminatedUserInput(szMovieTitle, MAX_MOVIE_TITLE);

                    //Getting the release year
                    do {

                        printf("Enter release year \r\n");

                        GetZeroTerminatedUserInput(pszBuffer, BUFFER_SIZE);
                        iReleaseYear = atoi(pszBuffer);

                        //Atoi returns zero if input are invalid
                        if (iReleaseYear == 0) {
                            printf("\x1b[31m"); //Prints red text
                            printf("Invalid input. Try again..\r\n");
                            printf("\x1b[0m");
                            usleep(1000000);
                        }

                    } while (iReleaseYear == 0);

                    //We summarize movie details and give the user the option to redo if needed.
                    printf("Movie: %s\r\nRelease year: %d\r\n", szMovieTitle, iReleaseYear);
                    printf("Continue or Edit movie (y or n)?\r\n");

                    memset(pszBuffer, 0, BUFFER_SIZE);

                    GetZeroTerminatedUserInput(pszBuffer, BUFFER_SIZE);

                } while (pszBuffer[0] != 'y');

                //At this point we got everything we need to create and insert movie.
                iRc = InsertMovie(&movieList,szMovieTitle,iReleaseYear);

                if(iRc == SUCCESS){
                    printf("\x1b[32m"); //Green success text
                    printf("Movie created:\r\n");
                    printf("\x1b[0m");
                    printf("Title: %s\r\n", szMovieTitle);
                    printf("Release year: %d\r\n", iReleaseYear);
                } else if(iRc == ERROR){
                    printf("\x1b[31m"); //Prints red text
                    printf("Failed to add movie to list.\r\n");
                    printf("\x1b[0m");
                }

                ToMainMenu();

                break;

            case MENU_OPTION_REMOVE_MOVIE:

                //Making sure buffer is set to null
                memset(szMovieTitle,0,MAX_MOVIE_TITLE);

                //Prompting user for title
                printf("Enter title to delete\r\n");
                GetZeroTerminatedUserInput(szMovieTitle,MAX_MOVIE_TITLE);

                iRc = DeleteMovieBasedOnTitle(&movieList,szMovieTitle);

                if(iRc == ERROR){
                    printf("\x1b[31m"); //Prints red text
                    printf("Failed to delete movie. Couldn't find title.\r\n");
                    printf("\x1b[0m");
                } else{
                    printf("\x1b[32m");
                    printf("Successfully deleted movie with title %s\r\n", szMovieTitle);
                    printf("\x1b[0m");
                }

                ToMainMenu();

                break;
            case MENU_OPTION_THREE:
                // Code to handle option three
                printf("Option 3 selected.\n");
                // ... (other code for option three)
                usleep(2000000);
                break;
            case MENU_OPTION_FOUR:
                // Code to handle option four
                printf("Option 4 selected.\n");
                // ... (other code for option four)
                usleep(2000000);
                break;
            case MENU_OPTION_EXIT:
                // Code to handle exit
                printf("Exiting..\n");
                usleep(2000000);
                break;
            default:
                // Code to handle invalid option
                printf("Invalid option selected.\n");
                usleep(2000000);
                break;
        }

    } while (eMenuOption != MENU_OPTION_EXIT);

    iRc = DeleteMovies(&movieList);

    if(iRc == ERROR){
        printf("An error occurred while freeing memory.");
    }

    return 0;
}

void ToMainMenu(){
    printf("Returning to main menu .");
    fflush(stdout); // Ensure the output is printed immediately
    usleep(750000); // Sleep for 500 milliseconds (0.5 seconds)

    printf(" .");
    fflush(stdout);
    usleep(750000); // Sleep for another 500 milliseconds

    printf(" .");
    fflush(stdout);
    usleep(750000); // Sleep for another 500 milliseconds

    printf("\r\033[K");
}