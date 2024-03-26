#include "include/utils.h"

void ToMainMenu(){
    printf("Returning to main menu .");
    fflush(stdout);
    usleep(750000);

    printf(" .");
    fflush(stdout);
    usleep(750000);

    printf(" .");
    fflush(stdout);
    usleep(750000);

    printf("\r\033[K");
}

void ExitProgram(){
    printf("Cleaning up and exiting .");
    fflush(stdout);
    usleep(750000);

    printf(" .");
    fflush(stdout);
    usleep(750000);

    printf(" .");
    fflush(stdout);
    usleep(750000);

    printf("\r\033[K");
}

