#include "include/menuapplication.h"
#include "include/sdlogger.h"
#include <stdio.h>

int main(int argc,char* argv[]){

    int choice = -1;

    choice = userInput('1','5');

    printf("%d\n", choice);

    return 0;

}