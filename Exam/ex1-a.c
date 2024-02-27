#include <stdio.h>
#include <stdlib.h>

void ReadTextFile(const char *fileName, char **pcBuffer ,long *lSize,char *mode);

int main(int argc,char* argv[]){

    char *pcBuffer = NULL;
    long lSize = 0;

    ReadTextFile("Exam/text.txt",&pcBuffer,&lSize,"rb");

    if(pcBuffer){

        int decimal = 0;

        while (*pcBuffer && *(pcBuffer + 1)){
            //Test atoi
            printf("First: %d\n", (int)*pcBuffer);
            printf("Second: %d\n", (int)*(pcBuffer+1));
            decimal = ((int)*pcBuffer * 16) + ((int)*(pcBuffer+1)*1);
            printf("%d",decimal);
            //printf("%c\n",decimal);
            pcBuffer += 2;
        }



    }


    return 0;

}

void ReadTextFile(const char *fileName, char **pcBuffer ,long *lSize,char *mode){


    FILE *f = fopen(fileName,mode);
    long lFileSize, lBufferSize;


    if(f != NULL){

        if(fseek(f,0,SEEK_END) == 0){
            lFileSize = ftell(f);
            rewind(f);

            *pcBuffer = (char *) malloc(lFileSize + 1);

            if(*pcBuffer == NULL){
                printf("Failed to allocate memory.");
                return;
            }

            lBufferSize = fread(*pcBuffer,sizeof (char),lFileSize,f);

            if(lBufferSize == lFileSize){
                //At this point we managed to read the whole file.
                *lSize = lFileSize;
                (*pcBuffer)[lFileSize] = 0;

            }

        } else{
            printf("Failed to calculate file size.");
            free(pcBuffer);
        }

    } else{
        printf("Didnt manage to read file.");
    }

}