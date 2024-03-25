#include "include/menu.h"

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


