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

    while (*d == ' '){
        ++d;
    }

    end = d;
    while (*end != '\0'){
        ++end;
    }

    end--;

    while (end > d && *end == ' '){
        --end;
    }

    *(end + 1) = '\0';

    //The pointer dosent include the last pointer, so I have to add 1.
    length = end - d + 1;

    printf("%lu\n", length);

    memmove(psText,d,length + 1);


}