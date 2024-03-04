#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char* argv[]){

    char *s = NULL;
    unsigned long length = 0;

    for(int i = 0; i < argc - 1; i++){
        length += strlen(argv[i + 1]);
    }

    s = (char *) malloc((length + 1) * sizeof (char));

    int index = 0;
    for(int j = 0; j < argc - 1;j++){
        strcpy(&s[index],argv[j + 1]);
        index += (int) strlen(argv[j+1]);
    }

    s[length] = '\0';

    printf("%s\n",s);

/*
    char *originalPointer = s;

    while (*s != '\0'){
        printf("%c\n",*s);
        s++;
    }


    s = originalPointer;
*/

    free(s);

}