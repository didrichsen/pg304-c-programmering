//
// Created by Simen Didrichsen on 07/03/2024.
//

#include <stdio.h>
#include "include/sdlogger.h"

typedef struct _HEADER {
    char  idlength;
    char  colourmaptype;
    char  datatypecode;
    short int colourmaporigin;
    short int colourmaplength;
    char  colourmapdepth;
    short int x_origin;
    short int y_origin;
    short width;
    short height;
    char  bitsperpixel;
    char  imagedescriptor;
} HEADER;


int main(void){

    HEADER sHeader;
    u_int8_t cBuff[2];


    FILE *pFile = fopen("img/sample_picture.tga", "rb");

    if(pFile == NULL){
        sderror("Failed to open file.");
        return 1;
    }

    fread(&cBuff[0], sizeof(u_int8_t ), 1, pFile);

    printf("%d\n",cBuff[0]);


    return 0;

}
