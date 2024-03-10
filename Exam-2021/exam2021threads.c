//
// Created by Simen Didrichsen on 10/03/2024.
//

#include "include/exam2021threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t BufferNotEmpty,BufferEmpty;

void *writingFile(void* args);

int main (int argc, char* argv[]) {

    //Input buffer
    char cInputBuffer[BUFFERSIZE];

    //Create worker
    pthread_t pThreadWork;

    //My struct
    BUFFER *pBuffer = malloc(sizeof(BUFFER));

    if (pBuffer == NULL) {
        perror("Failed to allocate memory for szInput");
        return 1;
    }

    pBuffer->pFile = NULL;
    pBuffer->iSize = 10;
    pBuffer->exitCode = 1;

    pBuffer->pFile = fopen("output.txt","a");

    sem_init(&pBuffer->BUFFERNOTEMPTY, 0, 0);
    sem_init(&pBuffer->BUFFEREMPTY, 0, 1);

    pthread_create(&pThreadWork,NULL, writingFile,(void*) pBuffer);

    printf("Write a sentence and hit 'Enter' to store in file. Write 'quit' to exit program.\n");

    //This will be the working era of the main thread.
    while (pBuffer->exitCode != 0) {


        //Getting an input string from user.
        //This can be BUFFERSIZE long, so we need the length.
        fgets(cInputBuffer,BUFFERSIZE,stdin);

        //Getting the length of the whole input.
        //This input should be transferred as 10 and 10 bytes
        unsigned long length = 0;

        char *pInputBuffer = cInputBuffer;

        //We will exit if either we reach the BUFFERSIZE or if we write exit.
        if(strstr(cInputBuffer,EXIT) == NULL){

            //I want to keep copying over 10 bytes at a time until
            //the length is bigger than strlen. Then I have copied everything.

            unsigned long inputSize = strlen(cInputBuffer);

            while (length <= inputSize) {

                //memset(pBuffer->cBuffer,0,sizeof (pBuffer->cBuffer));

                sem_wait(&pBuffer->BUFFEREMPTY);

                strncpy(pBuffer->cBuffer, &cInputBuffer[length], pBuffer->iSize);
                pBuffer->cBuffer[10] = 0;

                length += 10;

                sem_post(&pBuffer->BUFFERNOTEMPTY);

            }

        } else{
            pBuffer->exitCode = 0;
            memset(pBuffer->cBuffer,0,sizeof (pBuffer->cBuffer));
            sem_post(&pBuffer->BUFFERNOTEMPTY);
        }

    }

    pthread_join(pThreadWork,NULL);
    free(pBuffer);

    return 0;

}

void *writingFile(void* args){

    BUFFER *pBuffer = (void *) args;

    while (pBuffer->exitCode != 0){

        sem_wait(&pBuffer->BUFFERNOTEMPTY);

        fprintf(pBuffer->pFile,"%s",pBuffer->cBuffer);

        sem_post(&pBuffer->BUFFEREMPTY);

    }

    return NULL;

}