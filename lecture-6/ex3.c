#include <stdio.h>
#include <stdlib.h>

/*
Now if I take the word : "computer"

Encode it such that I only find the position of each character in the text and make sure
that each position is atleast seperated by 10 characters from the previous position.

My output will be :

101 133 200 218 236 253 282 314
C   O   M   P   U   T   E   R

Now write a program that takes a word from the user as an input and encode it as following:

-> All letters must be converted to positions
-> The output must be just the positions seperated by space
-> The positions must follow one specific rule : they must be seperated by atleast 10 characters.
-> If it is unable to complete the word - print error message and exit

Write a program that does the opposite - takes in a code and decodes it to the word.


*/

void main(void){

    FILE *f = NULL;
    char *pBuffer = NULL;
    long fileSize = 0, bufferSize;
    char word[30];


    f = fopen("lecture-6/adventures.txt","r");

    if(f != NULL){
        if(fseek(f,0,SEEK_END) == 0){
            fileSize = ftell(f);
            printf("Filesize = %ld\n", fileSize);
            rewind(f);

            pBuffer = malloc(fileSize + 1);

            if(pBuffer != NULL){
                bufferSize = fread(pBuffer,sizeof (char),fileSize,f);
                if(bufferSize == fileSize){
                    pBuffer[fileSize] = '\0';
                    for(int i = 0; i < fileSize;i++){
                        printf("%c", pBuffer[i]);
                    }
                }
            }

        }
    }

    printf("Type a word to encode and search for: \n");
    fgets(word, sizeof(word), stdin);

    //Vi ønsker å finne første occurrence av word[n]
    //Hente ut posisjon

    for (int i = 0; i < fileSize; ++i) {
        
    }



    free(pBuffer);


}