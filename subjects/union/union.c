//
// Created by simen on 3/6/2024.
//

#include <stdio.h>
#include <string.h>

union Data{
    int i;
    float f;
    char cBuffer[20];
};

int main(void){

    union Data uData;

    uData.i = 20;
    uData.f = 20.5;
    strcpy(uData.cBuffer,"Simen Didrichsen");

    printf("%d\n",uData.i); //Unpredictable value
    printf("%f\n",uData.f); //Unpredictable value
    printf("%s\n",uData.cBuffer); //Simen Didrichsen

}