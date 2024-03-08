/*
 Simulate a bank account that multiple threads wants to take out money from.
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_INTEGER_INPUT 10000

typedef struct _Transaction{
    int amount;
    int balance;
}Transaction;

int getInput();
void *withdrawal(void *tsDetails);

pthread_mutex_t pmMux = PTHREAD_MUTEX_INITIALIZER;

void main(void){

    pthread_t pThreadOne,pThreadTwo,pThreadThree;

    Transaction account;
    account.balance = 10000;

    pthread_create(&pThreadOne,NULL,withdrawal,(void*) &account);
    pthread_create(&pThreadTwo,NULL,withdrawal,(void*) &account);
    pthread_create(&pThreadThree,NULL,withdrawal,(void*) &account);

    printf("Amount left %d\n", account.balance);

    pthread_join(pThreadOne,NULL);
    pthread_join(pThreadTwo,NULL);
    pthread_join(pThreadThree,NULL);

    printf("Amount left %d\n", account.balance);


}

void *withdrawal(void *tsDetails){

    Transaction *stDetails = (Transaction *) tsDetails;

    pthread_mutex_lock(&pmMux);

    stDetails->amount = getInput();

    stDetails->balance -= stDetails->amount;

    pthread_mutex_unlock(&pmMux);

    return NULL;
}

int getInput(){

    char cBuffer [MAX_INTEGER_INPUT];
    int amount = 0;

    printf("Enter amount to withdraw: ");

    if ((fgets(cBuffer,MAX_INTEGER_INPUT,stdin)) != NULL){

        amount = atoi(cBuffer);
    }

    return amount;

}

