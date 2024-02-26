#include <stdio.h>

void main(void){

    FILE *f = fopen("./text.txt","r");
    FILE *fOut = fopen("./output.txt","w");

    int c;
    char s[100];
    int lineNumber = 1;

    if(f != NULL){
/*
        while (!feof(f)){
            if((c = fgetc(f)) != EOF){
                putchar(c);
            }
        }
        */
/*

        while ((fgets(s,100,f)) != NULL){
            printf("%d: %s", lineNumber, s);
            lineNumber++;
        }
        */

        while ((c = getc(f)) != EOF){
            putc(c,fOut);
        }

    }



    fclose(f);


}