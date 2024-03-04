#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define MAX_SIZE 100 // Maximum number of elements in the map

int size = 0; // Current number of elements in the map
int keys[MAX_SIZE]; // Array to store the keys
int values[MAX_SIZE]; // Array to store the values

// Function to get the index of a key in the keys array
int getIndex(int key)
{
    for (int i = 0; i < size; i++) {
        if (keys[i] == key) {
            return i;
        }
    }
    return -1; // Key not found
}

// Function to insert a key-value pair into the map
void insert(int key, int value)
{
    int index = getIndex(key);

    if (index == -1) { // Key not found
        if(size < MAX_SIZE){
            keys[size] = key;
            values[size] = value;
            size++;
        } else{
            printf("Map is full. Cannot insert more key-value pairs.");
        }
    }
}

// Function to get the value of a key in the map
int get(int key)
{
    int index = getIndex(key);
    if (index == -1) { // Key not found
        return -1;
    }
    else { // Key found
        return values[index];
    }
}

int calcFib(int number){

    int index;

    if(number == 0) {
        return 0;
    }

    if(number == 1 || number == 2){

        return 1;

    }

    if((index = getIndex(number)) != -1) {
        return get(number);
    }

    int result = calcFib(number-1) + calcFib(number-2);
    insert(number, result);
    return result;

    }

// Function to print the map
void printMap()
{
    for (int i = 0; i < size; i++) {
        printf("%d: %d\n", keys[i], values[i]);
    }
}

unsigned long GetTime() {
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec*(unsigned long)1000000+tv.tv_usec;
}


int main(int argc,char* argv[])
{

    unsigned long timeStart, timeEnd;

    timeStart = GetTime();
        
    int number = atoi(argv[1]);	

    int fib = calcFib(number);
    
    timeEnd = GetTime();

    printf("Fib of number %d are %d\n", number, fib);
    
    printf("The elapsed time is %lu ms", (timeEnd - timeStart)/1000);


    return 0;
}
