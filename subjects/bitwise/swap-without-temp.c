//
// Created by simen on 3/6/2024.
//

#include <stdio.h>

int main(void){

    int x, y;

    x = 10; //1010
    y = 5;  //0101

    //1010 XOR 0101
    //1111
    x ^= y;
    //0101 XOR 1111
    //1010
    y ^=x;
    //1111 XOR 1010
    //0101
    x^=y;

    printf("|x = %d| & |y = %d|", x,y);



    return 0;

}