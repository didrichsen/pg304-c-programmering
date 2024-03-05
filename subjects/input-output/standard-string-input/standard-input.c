/*

 Exploring ways to take standard-string-input from user in C.

 */


//#include "include/standard-string-input.h"
#include <stdio.h>
#include <string.h>

#define SZEOFBUFFER 100

int main(void ){

    char buffer[SZEOFBUFFER];
    int index;

    printf("Enter a string: ");

    //Returns NULL when newline character is encountered or end of file is reached: https://www.educative.io/answers/how-to-use-the-fgets-function-in-c
    if(fgets(buffer,sizeof (buffer),stdin) != NULL){

        //Removes the end of line character
        index = strcspn(buffer,"\n");

        //We remove the new line character.
        buffer[index] = 0;

    } else{
        //sderror("Failed to read string from standard-string-input.");
        return 1;
    }

    printf("Your string: %s\n",buffer);
    printf("Length of |%s| is |%llu|\n", buffer, strlen(buffer));

    return 0;

}