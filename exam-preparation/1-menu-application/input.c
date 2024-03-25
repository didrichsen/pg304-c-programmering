#include "include/input.h"

//Removes spaces, newline char and forces zero terminator to be the last char.
static void SanitizeInput (char *psText){

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

}

//Returns a zero terminated string not longer than iSize.
void GetZeroTerminatedUserInput(char *pszBufferDestination, int iSize){

    char szLocalBuffer[BUFFER_SIZE] = {0};
    int iInputValid;

    do {

        iInputValid = TRUE;

        fgets(szLocalBuffer,BUFFER_SIZE-1, stdin);

        //If strstr returns NULL it means input was too long since it wasent room for "\n"
        if((strstr(szLocalBuffer,"\n")) == NULL || strlen(szLocalBuffer) > iSize) {

            printf("Input to long.\r\n");
            //Empty buffer. We empty all the way until \n since there are still chars in the buffer.
            while (getchar() != '\n');

            iInputValid = FALSE;
        }

    } while (!iInputValid);

    SanitizeInput(szLocalBuffer);

    strncpy(pszBufferDestination,szLocalBuffer,iSize);

}
