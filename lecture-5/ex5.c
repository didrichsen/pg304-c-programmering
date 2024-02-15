#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <stdbool.h>

typedef struct {
    char cArr[3][3];
} BOT;

typedef struct _BOTLIST {
    struct _BOTLIST *psNext;
    BOT sThis;
} BOTLIST;

int printBot(BOT bot);
BOT createBot();
void createBotList(BOTLIST **headPtr);
int numberOfBots();
int playLevel(BOTLIST *psBots, int *iLife, int *iLevel, int *iKill, int *iTime);
void destroyBots(BOTLIST **headPtr);

int main(int argc, char *argv[]) {

    int iLife = 100;
    int iBots = 0;
    int botLife = 0;
    int iTime = 10;
    int iKills = 0;
    int iLevel = 1;
    BOTLIST *head = NULL;

    srand(time(NULL));

    initscr();
    printw("Lets go (outside while loop)!\n\n");

    while (iLife > 0) {

        clear();
        printw("Lets go!\n\n");
        //We calculate a random number between 2 -> 8 (inclusive)
        iBots = numberOfBots();
        int success = 0;

        //Create x number of bots and put in a Linked List.
        for (int i = 0; i < iBots; i++) {
            createBotList(&head);
        }

        success = playLevel(head,&iLife,&iLevel,&iKills,&iTime);
        destroyBots(&head);
        timeout(2000);getch();

        if(iLevel == 5){
            printw("Congratulations. Game GG, well played.\n\n");
            printw("You killed: %d", iKill);
            timeout(2000);
            break;
        }

    }

    endwin();

    return 0;

}

int printBot(BOT bot) {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printw("%c", bot.cArr[i][j]);
            if (bot.cArr[i][j] == '1') {
                sum++;
            }
        }
        printw("\n");
    }
    return sum;
}

void destroyBots(BOTLIST **headPtr) {
    BOTLIST *current = *headPtr;
    BOTLIST *next;

    while (current != NULL) {
        next = current->psNext;
        free(current);
        current = next;
    }

    // Update the head pointer in the calling function to NULL
    *headPtr = NULL;
}

int numberOfBots() {
    int numberOfBots = 2;//rand() % 3;

    //numberOfBots += 2;

    return numberOfBots;
}

BOT createBot() {
    int binary = 0;
    BOT bot;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            binary = rand() % 2;
            if (binary == 0) {
                bot.cArr[i][j] = '0';
            } else {
                bot.cArr[i][j] = '1';
            }
        }
    }
    return bot;
}

void createBotList(BOTLIST **headPtr) {
    //Create the BotList
    BOTLIST *newHead;

    newHead = (BOTLIST *) malloc(sizeof(BOTLIST));

    if (newHead == NULL) {
        printw("Memory allocation failed\n");
        exit(EXIT_FAILURE); // Terminate the program
    }

    //Create the new bot to be added
    BOT bot = createBot();
    // Initialize the new node with the provided data
    newHead->sThis = bot;
    // Make the new node point to the current head of the list
    newHead->psNext = *headPtr;
    // Update the head pointer to point to the new node
    *headPtr = newHead;
}

int playLevel(BOTLIST *psBots, int *iLife, int *iLevel, int *iKill, int *iTime){

    int botLife = 0;

    printw("Welcome to level %d\n\n", *iLevel);

    while (psBots){
        botLife = printBot(psBots->sThis);
        printw("Enter number of 1:\n\n");
        timeout(*iTime * 1000);
        int answer = getch() - '0';

        if(answer == botLife){
            (*iKill)++;
            printw("You killed the bot. Plus 5 points. \n\n");
        } else if(answer == -1){
            *iLife -= 10;
            printw("Times up. You lost 10 life. Try again. \n\n");
            break;
        } else{
            *iLife -= 5;
            printw("Level failed. You lost 5 life. Try again. \n\n");
            break;
        }

        timeout(2000); getch();
        psBots = psBots->psNext;

    }

    if(psBots == NULL){
        (*iLevel)++;
        *iTime -= 1;
        printw("Level cleared.\n\n");
        return 1;
    } else{
        printw("Level failed. \n\n");
        return 0;
    }

}

