#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

sem_t dataReady, spaceAvailable;

void *producer(void* args);
void *consumer(void* args);

int main(void) {
    int buffer = 0;

    // Threads
    pthread_t producerThread, consumerThread;

    // Create semaphores
    sem_init(&dataReady, 0, 0);         // No data is ready initially.
    sem_init(&spaceAvailable, 0, 1);    // Buffer is empty initially.

    // Create producer and consumer threads
    pthread_create(&producerThread, NULL, producer, (void*)&buffer);
    pthread_create(&consumerThread, NULL, consumer, (void*)&buffer);

    // Wait for the threads to finish
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Destroy semaphores
    sem_destroy(&dataReady);
    sem_destroy(&spaceAvailable);

    return 0;
}

void *producer(void* args) {
    int *buffer = (int*) args;
    for (int i = 0; i < 10; ++i) {
        sem_wait(&spaceAvailable);  // Wait for space to be available.
        *buffer = i;                // Produce data.
        printf("Produced: %d\n", *buffer);
        sem_post(&dataReady);       // Signal that data is ready.
    }
    return NULL;
}

void *consumer(void* args) {
    int *buffer = (int*) args;
    int consumed;
    for (int i = 0; i < 10; ++i) {
        sem_wait(&dataReady);       // Wait for data to be ready.
        consumed = *buffer;         // Consume data.
        printf("Consumed: %d\n", consumed);
        sem_post(&spaceAvailable);  // Signal that space is available.
    }
    return NULL;
}