//
// Created by Simen Didrichsen on 09/03/2024.
//

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//Threads should sleep until GOAL is reached by last thread.
#define GOAL 5

typedef struct _Number{
    int count;
}Number;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_not_equal = PTHREAD_COND_INITIALIZER;


void *letsCount(void *arg){

    Number *myNumber = (Number*) arg;

    pthread_mutex_lock(&mutex);

    myNumber->count++;

    if(myNumber->count != GOAL){
        printf("Thread sleeping and count are %d\n", myNumber->count);
        pthread_cond_wait(&cond_not_equal,&mutex);
    } else{
        pthread_cond_broadcast(&cond_not_equal);
    }


    //pthread_cond_signal(&cond_not_equal);
    
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void main(void){

    pthread_t myThreads[GOAL];
    Number *myNumber = malloc(sizeof (Number));

    myNumber->count = 0;

    for(int i = 0; i < GOAL; i++){
        pthread_create(&myThreads[i],NULL,letsCount,(void*)myNumber);
    }

    for(int j = 0; j < GOAL; j++){
        pthread_join(myThreads[j],NULL);
    }

    printf("Made it!");

    free(myNumber);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_not_equal);

}