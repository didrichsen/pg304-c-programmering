#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

#define SIZE_LIMIT 5

void printArray(unsigned int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
}

void swap(unsigned int array[], int size) {
    int i, j, temp;
    int swapped = FALSE;

    for (i = 0; i < size - 1; i++) {
        swapped = FALSE;
        for (j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
                swapped = TRUE;
            }
        }

        if (!swapped) {
            break;
        }
    }

    printArray(array, size);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        return 1; // Exit with an error code
    }

    int size = atoi(argv[1]);

    if (size < 0 || size > SIZE_LIMIT) {
        printf("Size should be between 0 and %d\n", SIZE_LIMIT);
        return 1; // Exit with an error code
    }

    int array[SIZE_LIMIT];

    for (int i = 0; i < size; i++) {
        array[i] = i + 1;  // Initialize array with consecutive numbers for testing
    }

    swap(array, size);

    return 0;
}
