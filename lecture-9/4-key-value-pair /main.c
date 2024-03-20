#include <stdio.h>
#include "include/keyvalue.h"
#include <string.h>
#include <string.h>
#include <stdlib.h>

int main(void){

    FILE *pFile = NULL;
    LIST *pHead = NULL;
    char cBuffer[BUFFFERSZE];
    char *pEqual=NULL;
    int keySize = 0;
    int valueSize = 0;
    char *pKey = NULL;
    char *pValue = NULL;
    int iNodeCounter = 1;
    int iRc = 0;

    pFile = fopen("keyvalue.txt","r");

    while (fgets(cBuffer,BUFFFERSZE,pFile) != NULL){

        int size = strlen(cBuffer);

        //We find the equal sign
        pEqual = strchr(cBuffer,'=');

        //We check that the buffer contains equal (or else it's an invalid sentence)
        if(pEqual != NULL){

            for(int i = 0; i < size; i++){
                if(cBuffer[i] == *pEqual){
                    keySize = i;
                }

                //We use the i - keysize - 1 to subtract everything before and including the equal sign
                if(cBuffer[i] == '\n'){
                    valueSize = i - keySize - 1;
                }
            }

            //At this point we have the size of the key and the value
            pKey = malloc(keySize);

            if(pKey != NULL){
                memset(pKey,0,keySize);
                for(int i = 0; i < keySize; i++){
                    pKey[i] = cBuffer[i];
                }
            }

            pValue = malloc(valueSize);

            if(pValue != NULL){
                memset(pValue,0,valueSize);
                for(int j = 0; j < valueSize; j++) {
                    pValue[j] = cBuffer[1 + keySize + j];
                }
            }

            InsertSorted(&pHead,pKey,pValue,valueSize);


            free(pKey);
            free(pValue);




        }

    }

    LIST *pCurrent = pHead;
    LIST *pTemp = NULL;

    while (pCurrent != NULL){
        pTemp = pCurrent;
        pCurrent = pCurrent->pNext;
        printNode(pTemp);
        free(pTemp);
    }



    return 0;
}