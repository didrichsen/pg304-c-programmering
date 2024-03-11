// Lession 8: ex2.c

#include <stdio.h>
#include <stdarg.h>

typedef unsigned char BYTE;

void PrintBinary(BYTE byNum)
{
   for (int i = 0; i < 8; i++) {
      printf ("%c", ((byNum & 0x80) >> 7) + '0');
      byNum <<= 1;
      // if (!((i + 1) % 4)) printf (" ");
   }
   printf ("\n");
}

int main(void)
{
   PrintBinary(0xFF);
   PrintBinary(0x10);
   PrintBinary(1);
   PrintBinary(-1);
   PrintBinary(255);
}
