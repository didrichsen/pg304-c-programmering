#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

typedef struct {
    char cArr[3][3];
} BOT;

typedef struct _BOTLIST {
    struct _BOTLIST *psNext;
    BOT sThis;
} BOTLIST;

BOT pickBot();

int main(int argc, char* argv[]){

    BOTLIST head;

    srand(time(NULL));

    pickBot();

    return 0;

}

BOT pickBot(){
    int min = 2;
    int max = 8;
    int numberOfBots = rand() % (max - min + 1) + min;

    printf("%d",numberOfBots);

}

