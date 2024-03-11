//
// Created by Simen Didrichsen on 11/03/2024.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (void) {

    char *cNumber = malloc(sizeof (char ) * 4);
    int number = -1;

    if(cNumber == NULL){
        printf("Failed to allocate memory.\n");
        return 1;
    }

    printf("Enter an 8 bit number (0-255): ");

    do {

        //Five, since we have zero terminator + new line
        fgets(cNumber,5,stdin);

        if((strstr(cNumber,"\n")) == NULL){

            while (getchar() != '\n');

            printf("Input to long. Only 8 bits.");

            number = -1;
        } else{

            number = atoi(cNumber);

            if (number < 0 || number > 255) {
                printf("8 bit number only. Please enter an 8 bit number (0-255): ");
                number = -1; // Reset number to -1 to continue the loop
            }

        }

    } while (number == -1);

    int shift = 1 << 7;//1000 0000

    for(int i = 0; i < 8; i++){
        printf("%s", shift & number ? "1" : "0");
        shift >>= 1;
    }
}
