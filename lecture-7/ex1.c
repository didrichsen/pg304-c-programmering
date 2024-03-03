#include <stdio.h>

void howManyTimeHaveIBeenCalled();

int main(void){

    for(int i = 0; i < 10; i++){
        howManyTimeHaveIBeenCalled();
    }

}

void howManyTimeHaveIBeenCalled(){

    static int count;

    //Nice way to see the difference betwen count++ and ++count
    //printf("I have now been called %d time%c\n",count++,count == 1? ' ' : 's');
    printf("I have now been called %d time%c\n",++count,count == 1? ' ' : 's');

}