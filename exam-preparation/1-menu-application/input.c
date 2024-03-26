#include "include/input.h"

//Removes spaces, newline char and forces zero terminator to be the last char.
//Returns length of string minus zero terminator
static int SanitizeInput (char *psText){

    char *d;
    char *end;
    long length;

    d = psText;

    //Whitespace in front
    //Move until I hit first character
    while (*d == ' '){
        ++d;
    }

    end = d;
    //Move end to newline character
    while (*end != '\0' && *end != '\n'){
        ++end;
    }

    if(*end == '\n'){
        *end = '\0';
    }

    //Moving end back from zero terminator
    end--;

    //Moving it back until it hits the last character
    while (end > d && *end == ' '){
        --end;
    }

    //Adding zero terminator
    *(end + 1) = '\0';

    //The pointer arithmetic doesn't include the last pointer when calculating addresses, so I have to add 1.
    length = end - d + 1;

    //Using memmove since im copying from same memory space. Safer than memcopy.
    //I add +1 to account for \0
    memmove(psText,d,length + 1);

    return length;

}

//Returns a zero terminated string not longer than iSize.
void GetZeroTerminatedUserInput(char *pszBufferDestination, int iSize) {
    char szLocalBuffer[BUFFER_SIZE] = {0};
    int iInputValid = FALSE;

    do {
        // Write to buffer
        fgets(szLocalBuffer, BUFFER_SIZE, stdin);

        // Check if only 'Enter' was pressed
        if (szLocalBuffer[0] == '\n') {
            printf("\x1b[31m"); // Prints red text
            printf("Only 'Enter' pressed.\r\n");
            printf("\x1b[0m");
        } else if (strchr(szLocalBuffer, '\n') == NULL) {
            // Check if the newline is present in the buffer
            // Flush the buffer if the newline is not present
            printf("\x1b[31m"); // Prints red text
            printf("Input too long for buffer.\r\n");
            printf("\x1b[0m");
            while (getchar() != '\n' && !feof(stdin));
            iInputValid = FALSE;
        }else {
            // Sanitize the input
            int length = SanitizeInput(szLocalBuffer);

            // Checks if the length is zero after sanitize. If so, only spaces were entered.
            if (length == 0) {
                printf("\x1b[31m"); // Prints red text
                printf("Only 'space' was registered.\r\n");
                printf("\x1b[0m");
            }
                // Check if input is too long after sanitization
            else if (length >= iSize) {
                printf("\x1b[31m"); // Prints red text
                printf("Input too long.\r\n");
                printf("\x1b[0m");
            } else {
                iInputValid = TRUE;
            }

        }
    } while (!iInputValid);

    // Copy the sanitized input to the destination buffer
    strncpy(pszBufferDestination, szLocalBuffer, iSize - 1);
    pszBufferDestination[iSize - 1] = '\0'; // Ensure null termination
}
