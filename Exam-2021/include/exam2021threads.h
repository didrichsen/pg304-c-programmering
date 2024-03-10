//
// Created by Simen Didrichsen on 10/03/2024.
//

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#ifndef PG304_C_PROGRAMMERING_EXAM2021THREADS_H
#define PG304_C_PROGRAMMERING_EXAM2021THREADS_H

sem_t BufferNotEmpty,BufferEmpty;

typedef struct _BUFFER{

    char cBuffer[11];
    FILE *pFile;
    int iSize;
    int exitCode;
    sem_t BUFFERNOTEMPTY;
    sem_t BUFFEREMPTY;

}BUFFER;

#define BUFFERSIZE 1024
#define EXIT "quit"


#endif //PG304_C_PROGRAMMERING_EXAM2021THREADS_H
