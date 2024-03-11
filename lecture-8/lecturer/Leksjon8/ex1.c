// Lession 8: ex1.c
//
// Target file format: https://en.wikipedia.org/wiki/Truevision_TGA

#include <stdio.h>
#include <stdarg.h>

#pragma pack(1)

typedef unsigned char UINT8;
typedef unsigned short UINT16;

typedef struct _COLOR_MAP_SPEC {
  UINT16 IdxFirstColorMap;
  UINT16 ColorMapSize;
  UINT8  BitsPerPixel;
} COLOR_MAP_SPEC;

typedef struct _IMAGE_SPEC {
  UINT16 OriginX;
  UINT16 OriginY;
  UINT16 Width;
  UINT16 Heigth;
  UINT8  BitsPerPixel;
  UINT8  ImageDescr;
} IMAGE_SPEC;

typedef struct _TARGA_HEADER {
  UINT8 IdLength;
  UINT8 ColorMapType;
  UINT8 ImageType;
  COLOR_MAP_SPEC ColorMapSpec;
  IMAGE_SPEC ImageSpec;
} TARGA_HEADER;

#pragma pack()

typedef unsigned char BYTE;

int main (int iArgC, char *apszArgV[])
{
   FILE *f;
   TARGA_HEADER sHeader;
/*
   if (iArgC < 2) {
      printf ("Targa decoder: Usage ./ex1 <file name>.\n");
      return 1;
   }
   */

   f = fopen ("sample_picture.tga", "rb");
   if (f != NULL) {
      if (fread (&sHeader, sizeof(sHeader), 1, f) == 1) {
         printf ("Image width : %d (pixels).\nImage heigth: %d (pixels).\n", sHeader.ImageSpec.Width, sHeader.ImageSpec.Heigth);
         switch (sHeader.ImageType) {
            case 0:
               printf ("0: Image type??\n");
               break;

            case 1:
               printf ("1: Uncompressed color-mapped image.\n");
               break;

            case 2:
               printf ("1: Uncompressed true-color image.\n");
               break;

            case 3:
               printf ("1: Uncompressed black-white image.\n");
               break;

            case 9:
               printf ("9: RLE compressed color-mapped image.\n");
               break;

            case 10:
               printf ("10: RLE compressed true-color image.\n");
               break;

            case 11:
               printf ("11: RLE compressed black-white image.\n");
               break;
         }
      }
      fclose(f);
   }
   else {
      printf ("Cannot open %s.\n", apszArgV[1]);
      return 1;
   }
   return 0;
}
