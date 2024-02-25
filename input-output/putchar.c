#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
/*
    char *string = NULL;

    string = (char*) malloc(100 * sizeof (char ));

    int age = 30;

    sprintf(string,"Im am %d years old.", age);


    printf("%s", string);

    free(string);
    */

FILE *f = NULL;

char szLine[160];

int iLine = 0;

f = fopen("test.txt", "r");

if(f != NULL){
    //While feof dosent return end of file
    while (!feof(f)){
        if(fgets(szLine,sizeof (szLine),f)){
            printf("test");
            printf("%d :%s", ++iLine,szLine);
        }
    }
}

fclose(f);


    return 0;



}