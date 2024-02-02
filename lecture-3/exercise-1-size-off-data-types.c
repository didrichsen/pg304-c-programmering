#include <stdio.h>



int main (int argc,char *argv[]){

int a;
unsigned int a2; 
float b; 
double c; 
long d;
int array[100];
char myChar;
int *ab;

int sizeInt = sizeof(a);
int sizeUnsignedInt = sizeof(a2);
int sizeFloat = sizeof(b);
int sizeDouble = sizeof(c);
int sizeOfLong = sizeof(d);
int sizeOfArray = sizeof(array)/sizeof(int);
int sizeOfChar = sizeof(myChar);
int sizeOfPointer = (int) sizeof(ab);

printf("The size of one int on my computer: %d\n",sizeInt);
printf("The size of one usigned int: %d\n", sizeUnsignedInt);
printf("The size of one float: %d\n", sizeFloat);
printf("The size of one double: %d\n", sizeDouble);
printf("The size of one long: %d\n", sizeOfLong);
printf("Number of ints that can be added to array: %d\n", sizeOfArray);
printf("One char has the size of: %d\n", sizeOfChar);
printf("Size of int pointer: %d\n", sizeOfPointer);

}
