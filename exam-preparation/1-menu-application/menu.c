#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    printf("Enter your menu option followed by ENTER: \n");
    printMenu();

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