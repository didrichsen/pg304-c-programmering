#ifndef INPUT_H
#define INPUT_H

// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./common.h"

// Define constants for buffer size
#define BUFFER_SIZE 1024

#define TRUE 1
#define FALSE 0

// Function prototypes
void GetZeroTerminatedUserInput(char *pszBufferDestination, int iSize);

#endif // INPUT_H