#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int stringLength(char array[]);

int main (int argc, char* argv[]){

    int size = 0;

    if(argc < 2){
        printf("Enter a string (in quotes if you have spaces)\n");
        return 1;
    }

    char* s = argv[1];

    size = stringLength(s);

    printf("Size of string are: %d\n", size);

    return 0;

}

int stringLength(char array[]){

    int i = 0, count = 0;

    while (array[i] != '\0'){
        printf("Array[%d] is equal to: %c\n", i, array[i]);
        i++;
        count++;
    }

    printf("At array[%d] is the zero terminator: %d (Printed as ASCII characters since its not visible as char)\n", i, array[i]);

    return count;

}