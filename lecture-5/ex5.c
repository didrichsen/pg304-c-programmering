#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ncurses.h>

    typedef struct {
        char cArr[3][3];
    } BOT;

    typedef struct _BOTLIST {
        struct _BOTLIST *psNext;
        BOT sThis;
    } BOTLIST;

    int printBot(BOT bot);
    BOT createBot();
    void createBotList(BOTLIST **head);
    void inputUser(int time, int *input);
    int numberOfBots();
    void getBotFromLinkedList(BOTLIST **head);

    int main(int argc, char *argv[]) {

        int life = 100, input = 0, bots = 0, i = 0, botLife = 0, score = 0, iTime = 10000;
        BOTLIST *head = NULL;

        initscr();

        srand(time(NULL));


        while (life) {
            //We calculate a random number between 2 -> 8 (inclusive)
            bots = numberOfBots();

            //Create x number of bots and put in a Linked List.
            for (; i < bots; i++) {
                createBotList(&head);
            }

            while (life) {
                getBotFromLinkedList(&head);
                if(head == NULL){
                    printw("Congratulations - level passed!\n");
                    break;
                }
                botLife = printBot(head->sThis);
                inputUser(iTime, &input);

                if (input != botLife || input == -49) {
                    if(input == -49){
                        printw("\nTimeout, -10 life\n");
                        life -= 10;
                    } else{
                        printw("\nWrong answer, -5 life\n");
                        life -= 5;
                    }
                } else {
                    printw("\nCorrect, +5 life\n");
                    life += 5;
                }
            }

            iTime -= 1000;

            if(iTime == 5000){
                printw("Congrats, you won!");
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

    int numberOfBots() {
        int numberOfBots = rand() % 7;

        numberOfBots += 2;

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

    void inputUser(int time, int *input) {

        printw("Enter your answer: \n");
        timeout(time);
        *input = getch() - '0';
    }

    void createBotList(BOTLIST **head) {
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
        newHead->psNext = *head;
        // Update the head pointer to point to the new node
        *head = newHead;
    }

    void getBotFromLinkedList(BOTLIST **head){

            if(head == NULL){
                printw("Within head == null");
                return;
            }

            //Create bot and extract the bot from the BOTLIST struct.
            //BOT firstBot = (*head)->sThis;
            //Store the current head in a temp before deleting/freeing memory
            BOTLIST *temp = *head;
            //Setting the head pointer to point at the next BOTLIST.
            *head = (*head)->psNext;
            //Freeing the memory of old head.
            free(temp);
    }

