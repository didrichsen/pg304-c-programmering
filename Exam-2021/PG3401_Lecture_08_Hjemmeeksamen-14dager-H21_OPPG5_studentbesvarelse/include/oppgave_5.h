#ifndef _THREADING_H_
#define _THREADING_H_

#include <semaphore.h>
#include <stdio.h>

typedef struct _BUFFER {
    char szBuffer[11];
    FILE *f;
    sem_t semNewTask;
    sem_t semTaskCompleted;
    int iExitProgram;
} BUFFER;

void *workerThread(void *buffer);

#endif // ndef _THREADING_H_