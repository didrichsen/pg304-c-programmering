//
// Created by Simen Didrichsen on 21/03/2024.
//


#include <string.h>
#include <stdio.h>

void TrimSpaces (char *psText);

int main(void){

    int size = 0;

    char pszBuffer[] = "    Simen Didrichsen ";

    size = strlen(pszBuffer);

    printf("Size before removing whitespace: %d\n", size);

    TrimSpaces(pszBuffer);

    size = strlen(pszBuffer);

    printf("Size after removing whitespace from string %s : %d\n", pszBuffer, size);

}

void TrimSpaces (char *psText){

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
    //Move end to zero terminator
    while (*end != '\0'){
        ++end;
    }

    end--;

    //Moving end back from zero terminator
    //Moving it back until it hits the last character
    while (end > d && *end == ' '){
        --end;
    }

    //Adding zero terminator
    *(end + 1) = '\0';

    //The pointer arithmetic dosent include the last pointer when calculating addresses, so I have to add 1.
    length = end - d + 1;

    //Using memmove since im copying from same memory space. Safer than memcopy.
    //I add +1 to account for \0
    memmove(psText,d,length + 1);


}