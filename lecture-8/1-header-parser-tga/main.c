#include <stdio.h>
#include <stdlib.h>

typedef unsigned char UINT8;
typedef short int INT16;

#pragma pack(1)
typedef struct _HEADER {
    UINT8 idlength;
    UINT8  colourmaptype;
    UINT8 datatypecode;
    INT16 colourmaporigin;
    INT16 colourmaplength;
    UINT8 colourmapdepth;
    INT16 x_origin;
    INT16 y_origin;
    INT16 width;
    INT16 height;
    UINT8  bitsperpixel;
    UINT8  imagedescriptor;
} HEADER;
#pragma pack()

void printDataType(UINT8 datatypecode);

int main(void) {
    HEADER sHeader;
    FILE *pFile = fopen("img/scg_logo.tga", "rb");

    if (pFile == NULL) {
        printf("Failed to read file.\n");
        return 1;
    }

    // Read the header
    if (fread(&sHeader, sizeof(HEADER), 1, pFile) != 1) {
        printf("Failed to read header.\n");
        fclose(pFile);
        return 1;
    }

    printf("Image width (pixels): %d\n", sHeader.width);
    printf("Image height (pixels): %d\n", sHeader.height);
    printDataType(sHeader.datatypecode);

    return 0;
}

void printDataType(UINT8 datatypecode){

    switch (datatypecode) {
        case 0:
            printf("No image data included.\n");
            break;
        case 1:
            printf("Uncompressed, color-mapped images.\n");
            break;
        case 2:
            printf("Uncompressed, RGB images.\n");
            break;
        case 3:
            printf("Uncompressed, black and white images.\n");
            break;
        case 9:
            printf("Runlength encoded color-mapped images.\n");
            break;
        case 10:
            printf("Runlength encoded RGB images.\n");
            break;
        case 11:
            printf("Compressed, black and white images.\n");
            break;
        case 32:
            printf("Compressed color-mapped data, using Huffman, Delta, and runlength encoding.\n");
            break;
        case 33:
            printf("Compressed color-mapped data, using Huffman, Delta, and runlength encoding. 4-pass quadtree-type process.\n");
            break;
        default:
            printf("Unknown data type.\n");
            break;
    }
}