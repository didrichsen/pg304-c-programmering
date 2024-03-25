#ifndef MENU_H
#define MENU_H

// Standard headers
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom headers
#include "./movie.h"
#include "./input.h"
// Enum for menu options
enum MENUOPTIONS {
    MENU_OPTION_ADD_MOVIE,
    MENU_OPTION_REMOVE_MOVIE,
    MENU_OPTION_ADD_ACTOR,
    MENU_OPTION_VIEW_ALL_MOVIES,
    MENU_OPTION_EXIT,
    MENU_OPTION_NOT_INITIALIZED
};

// Function prototypes
enum MENUOPTIONS GetMenuOption();
void ViewAllMovies(MOVIE_LIST *pList);

#endif // MENU_H