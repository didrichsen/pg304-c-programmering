#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main (int argc,char * argv[]){

    FILE *pFile = NULL;
    int numberOfTimes[26];
    int c;
    int index;

    memset(numberOfTimes,0,sizeof (numberOfTimes));

    pFile = fopen("outputText.txt","r");

    if(pFile != NULL){

        while ((c = getc(pFile)) != EOF ){
            c = tolower(c);
            if(c > 96 && c < 123){
                index = c - 'a';
                numberOfTimes[index]++;
            }
        }
    }

    for(int i = 0; i < 26; i++){
        printf("Letter: %c - %d times\n", i + 'a',numberOfTimes[i]);
    }

    fclose(pFile);

}