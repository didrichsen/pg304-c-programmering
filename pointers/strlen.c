#include <stdio.h>

/*
 * Shows how pointer, array and string constant can be passed to function that
 * expects char pointer. Also demonstrates how you can increment pointer within
 * a loop. It then uses its own copy to move on to the next char in array.
 */

int strlen(char *s);

int main(int argc,char *argv[]){

    int length = 0;
    char *s = "Whats up man!";

    char array[6];
    array[0] = 'S';
    array[1] = 'i';
    array[2] = 'm';
    array[3] = 'e';
    array[4] = 'n';
    array[5] = '\0';



    length = strlen(s);

    printf("%d, length of pointer are\n", length);

    //When passing array name you are really passing the address of the array.
    length = strlen(array);

    printf("%d, length when passing array\n", length);

    length = strlen("Hello, World!");

    printf("%d, length when passing string constant\n", length);

    //Passing address of the third array object.
    length = strlen(&array[2]);

    printf("%d, length when passing sub-array\n", length);

    //Alternative way of passing sub-array.
    length = strlen(array+2);

    printf("%d, length when passing sub-array\n", length);




}

int strlen(char *s){

    int n = 0;

    for(; *s != '\0'; s++){
        n++;
    }

    return n;

}