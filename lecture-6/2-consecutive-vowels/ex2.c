#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*

 Exercise 2:

Download a book from project gutenburg and find the number of occurences of the following:

-> two consecutive vowels
-> a specific letter followed immediately by the same letter
-> a pair of letters seperated by atleast 'm' and atmost 'n' characters

Try this first on a small piece of text to verify the correctness.

 */

int isVowel(int c);
void countConsecutiveVowels(FILE *f);
void findTwoConsecutiveLetters(FILE *f);

void main(void){

    FILE *f = fopen("lecture-6/smallText.txt", "r");

    if(f != NULL){
        countConsecutiveVowels(f);
    }

    fclose(f);
}

void countConsecutiveVowels(FILE *f){
    int vowelCounter = 0;
    int c;
    int nextCharacter = 0;

    while ((c = fgetc(f)) != EOF){
        c = tolower(c);

        if(isVowel(c)){
            if((nextCharacter = fgetc(f)) != EOF && isVowel(nextCharacter)){
                vowelCounter++;
            }
        }
    }

    printf("Number of two vowels in a row %d", vowelCounter);

}

void findTwoConsecutiveLetters(FILE *f){

    char

    while (){
        printf("%d",*f)
    }

}

int isVowel(int c){
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
        return 1;
    } else{
        return 0;
    }
}