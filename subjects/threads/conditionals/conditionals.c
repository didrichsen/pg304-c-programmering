#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;

// Mutex and condition variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_not_full = PTHREAD_COND_INITIALIZER;

// Producer function
void* producer(void* arg) {
    for (int i = 0; i < 100; ++i) {
        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE) { // Buffer is full
            pthread_cond_wait(&cond_not_full, &mutex);
        }
        buffer[count] = i; // Produce item
        count++;
        printf("Produced nr, %d\n",count);
        pthread_cond_signal(&cond_not_empty); // Signal consumer that buffer is not empty
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    for (int i = 0; i < 100; ++i) {
        pthread_mutex_lock(&mutex);
        while (count == 0) { // Buffer is empty
            pthread_cond_wait(&cond_not_empty, &mutex);
        }
        int item = buffer[count-1]; // Consume item
        count--;
        printf("Consumed: %d\n", item);
        pthread_cond_signal(&cond_not_full); // Signal producer that buffer is not full
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}