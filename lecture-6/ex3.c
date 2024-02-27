#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Now if I take the word : "computer"

Encode it such that I only find the position of each character in the text and make sure
that each position is atleast seperated by 10 characters from the previous position.

My output will be :

101 133 200 218 236 253 282 314
C   O   M   P   U   T   E   R

Now write a program that takes a word from the user as an input and encode it as following:

-> All letters must be converted to positions | Check
-> The output must be just the positions seperated by space | Check
-> The positions must follow one specific rule : they must be seperated by atleast 10 characters. | Check
-> If it is unable to complete the word - print error message and exit

Write a program that does the opposite - takes in a code and decodes it to the word.


*/

int main(int argc, char *argv[]){

    FILE *f = NULL;
    char *pBuffer = NULL;
    long fileSize = 0, bufferSize;
    char *pWord = NULL;
    int *pEncoded = NULL;
/*
    if(argc < 2){
        printf("Usage: ex3 <Insert a word to encode>.\n");
        return 1;
    }
    */


    f = fopen("lecture-6/adventures.txt","rb");

    if(f != NULL){
        if(fseek(f,0,SEEK_END) == 0){
            fileSize = ftell(f);
            rewind(f);

            pBuffer = (char *) malloc(fileSize + 1);

            if(pBuffer != NULL){
                bufferSize = fread(pBuffer,sizeof (char),fileSize,f);
                if(bufferSize == fileSize){
                    pBuffer[fileSize] = 0;

                    pWord = "Simen";//argv[1]; //Start of word.
                    char *pBufferIterator = pBuffer;

                    //While loop conditions:
                    //*pWord will be false when reaching zero terminator.
                    //pBufferIterator has to be within the memory range
                    //pBufferIterator will be NULL when reaching zero terminator.
                    while (*pWord && (pBufferIterator < (pBuffer + fileSize)) && (pBufferIterator != NULL)){
                        //Return pointer to character if found, else NULL if the char is not found in string.
                        pBufferIterator = strchr(pBufferIterator,*pWord);
                        if(pBufferIterator != NULL){
                            //If come inside here, it means we found the char.
                            //We are calculating location based on memory address.
                            printf("%c encoded to %lld\n",*pWord,pBufferIterator - pBuffer);
                            //At this point pBufferIterator are pointing to an index and we need to
                            //adjust it 10 places ahead.
                            pBufferIterator += 10;
                            pWord++;
                        }
                    }

                    if(*pWord) {
                        printf("Couldn't finish word");
                        return -1;
                    }

                }
            }
        }
    }


    free(pBuffer);

    return 0;


}