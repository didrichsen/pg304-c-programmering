#include <stdio.h>

/*
 * Exercise 3:
 * Take an input string and print all the occurrences of vowels[a,e,i,o,u] in the
 * string in order of their occurrence.
 * Try to accomplish this task in 2 ways:
 *   1. An integer traversing the string by index
 *   2. A pointer traversing the string
 */

int checkIfVowel(char s);
void printVowels(char s[]);

int main(int argc, char* argv[]) {
    char *s = argv[1];
    printVowels(s);
    return 0;
}

void printVowels(char s[]) {
    int i = 0;
    printf("Vowels printed using pointer increase:\n");
    char *origin = s;

    while (*s != '\0') {
        if (checkIfVowel(*s)) {
            printf("Address %p has vowel: %c\n", s, *s);
        }
        s++;
    }

    s = origin;

    printf("Vowels printed using integer and index:\n");

    while (s[i] != '\0') {
        if (checkIfVowel(s[i])) {
            printf("Place %d has vowel: %c\n", i, s[i]);
        }
        i++;
    }
}

int checkIfVowel(char s) {
    switch (s) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return 1;
        default:
            return 0;
    }
}
