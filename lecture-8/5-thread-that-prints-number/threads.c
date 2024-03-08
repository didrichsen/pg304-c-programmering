/*
Exercise 5:

Play with pthreads library. Try to accomplish the following

-create a thread that prints numbers
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct _iData{
    int number;
}iData;

void *printNumber (void *number){
    iData *num = (iData *) number;
    printf("%d\n", num->number);

    return NULL;
}

int main(void){

    pthread_t pThread;
    iData *pData = malloc(sizeof (iData));

    pData->number = 100;

    pthread_create(&pThread,NULL,printNumber,(void*) pData);

    pthread_join(pThread, NULL);

    free(pData);



}