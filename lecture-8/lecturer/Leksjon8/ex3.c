// Lession 8: ex3.c

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

int RotateLeft (BYTE *pbyRing, int iBits)
{
   BYTE byCarry;
   BYTE byMask;

   byMask = 0xFF << (8 - iBits);  // Make mask
   byCarry = (*pbyRing & byMask);
   byCarry >>= (8 - iBits);
   *pbyRing <<= iBits;
   *pbyRing |= byCarry;
}

int RotateRight (BYTE *pbyRing, int iBits)
{
   BYTE byCarry;
   BYTE byMask;

   byMask = 0xFF >> (8 - iBits);  // Make mask
   byCarry = (*pbyRing & byMask);
   byCarry <<= (8 - iBits);
   *pbyRing >>= iBits;
   *pbyRing |= byCarry;
}

int main(void)
{
   BYTE byRing;           // Just use one byte...
   byRing = 0x42;         // 0100 0010
   PrintBinary(byRing);

   RotateLeft (&byRing, 2);
   PrintBinary(byRing);

   RotateRight (&byRing, 2);
   PrintBinary(byRing);

   RotateRight (&byRing, 3);
   PrintBinary(byRing);

   RotateLeft (&byRing, 3);
   PrintBinary(byRing);

}
