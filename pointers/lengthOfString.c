#include <stdio.h>

int lengthOfString(char *s){

    int n;

    for(n = 0; *s != '\0'; s++){
        n++;
    }

    return n;

}

int main(int argc, char* argv[]) {

    int length;

    char array[10];

    array[0] = 'S';
    array[1] = 'i';
    array[2] = 'm';
    array[3] = 'e';
    array[4] = 'n';
    array[5] = '\0';

    length = lengthOfString(array);

    printf("Length of Simen are %d \n", length);


    int lengthFromI = lengthOfString(&array[1]);

    printf("Its possible to set the pointer to start somewhere else in the array, for example i, length = %d \n", lengthFromI);

    lengthFromI = lengthOfString(array+2);

    printf("Another way of passing pointer, %d \n", lengthFromI);

}