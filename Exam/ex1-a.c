#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void ReadTextFile(const char *fileName, char **pcBuffer ,long *lSize,char *mode);
int HexToDec(char c);

int main(int argc,char* argv[]){

    char *pcBuffer = NULL;
    FILE *pFile = NULL;
    long lSize = 0;
    char *cFileName = "Exam/text.txt";

    ReadTextFile(cFileName,&pcBuffer,&lSize,"rb");
    pFile = fopen("Exam/outputText.txt","w");

    if(pcBuffer != NULL){

        int iDecimalA;
        int iDecimalB;

        for(int i = 0; i < lSize - 1; i += 2){

            iDecimalA = HexToDec(pcBuffer[i]) * 16;

            iDecimalB = HexToDec(pcBuffer[i+1]);

            fputc(iDecimalA+iDecimalB,pFile);


        }
    }

    free(pcBuffer);

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

int HexToDec(char c) {

    if(c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F'){
        c = tolower(c);
    }

    switch (c) {
        case 'a':
            return 10;
            break;
        case 'b':
            return 11;
            break;
        case 'c':
            return 12;
            break;
        case 'd':
            return 13;
            break;
        case 'e':
            return 14;
            break;
        case 'f':
            return 15;
            break;
        default:
            return c - '0';
            break;
    }
}
