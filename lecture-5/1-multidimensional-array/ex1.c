#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void BubbleSort(int array[], int iSze);
void Swap(int *pA, int *pB);

int main() {
    int row = 0, col = 0, numInputs = 0, userInput = 0, i = 0, iRand = 0, counter = 0;
    int **iArray = NULL;
    int *usedRows = NULL;

    // Get the number of rows and columns from the user
    while (numInputs != 2) {
        printf("Enter number of rows: ");
        numInputs += scanf("%d", &row);
        printf("Enter number of columns: ");
        numInputs += scanf("%d", &col);
    }

    // Allocate memory for the array and usedRows array
    iArray = (int **)malloc(row * sizeof(int *));
    usedRows = (int *)malloc(row * sizeof(int));
    for (i = 0; i < row; i++) {
        iArray[i] = (int *)malloc(col * sizeof(int));
        usedRows[i] = 0; // Initialize usedRows to 0 so I can compare and see if row is filled.
    }

    // Fill the array with user input
    srand(time(NULL));
    while (counter != row) {
        //Generate a random number between 0 -> but not included row
        iRand = rand() % row;
        //Checks if row is used earlier (its used if its value are 1)
        if (usedRows[iRand] == 0) {
            printf("Filling row %d\n", iRand);
            for (int c = 0; c < col; c++) {
                printf("Input number for column %d: ", c);
                scanf("%d", &userInput);
                iArray[iRand][c] = userInput;
            }
            usedRows[iRand] = 1; // Mark the row as used
            counter++; //Increment counter so we can leave the loop when all rows are filled.
        }
    }

    // Sort each row of the array
    for (i = 0; i < row; i++) {
        //Passing in pointer i which within the bubble sort will act as the first element in its array.
        BubbleSort(iArray[i], col);
    }

    // Print the sorted array
    printf("Sorted Array:\n");
    for (int p = 0; p < row; p++) {
        printf("\n┌-----------------------┐\n");
        for (int q = 0; q < col; q++) {
            printf("│ %d ", iArray[p][q]);
        }
        printf("│\n└-----------------------┘\n");
    }

    // Free allocated memory
    for (i = 0; i < row; i++) {
        free(iArray[i]);
    }
    free(iArray);
    free(usedRows);

    return 0;
}

void BubbleSort(int array[], int iSze) {
    int bHasSwapped = 1;
    while (bHasSwapped) {
        bHasSwapped = 0;
        for (int i = 1; i < iSze; i++) {
            if (array[i - 1] > array[i]) {
                Swap(&array[i - 1], &array[i]);
                bHasSwapped = 1;
            }
        }
    }
}

void Swap(int *pA, int *pB) {
    int pTmp;
    pTmp = *pA;
    *pA = *pB;
    *pB = pTmp;
}