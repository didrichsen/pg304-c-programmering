/* KASSEAPPARAT.C header file -----------------------------------------------------------------

 Project     : Exam PG3401 H21 - Oppgave 3
 Author      : Bengt Østby
 Revision    : 1.0
 Description : Implementation of cash register for oppgave 3

--------------------------------------------------------------------------------------------*/



/*=== Standard C library: ===============================================================
=======================================================================================*/

#define _CRT_SECURE_NO_WARNINGS // Dangerous and we would never do this, except this is a luddite course
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

/*=== Project spesific include files: ===================================================
=======================================================================================*/

#include "pgdbglog.h"

#include "kasseapparat.h"

/*=== (): ============================================================
 Author      : Bengt Østby
 Revision    : 1.0


 Comments regarding grading:
 
=======================================================================================*/

void PrintCashRegisterScreen(void) {
#ifdef _WIN32
   system("cls");
#else
   system("clear");
#endif
   printf("\r\nKasseapparat Applikasjon 1.0\r\n\r\n");
   printf("\r\nPress 1 to ADD ITEM");
   printf("\r\nPress 2 to DELETE LAST ITEM");
   printf("\r\nPress 3 to DELETE ITEM");
   printf("\r\nPress 4 to GET TOTAL");
   printf("\r\nPress 5 to PRINT RECEIPT");
   printf("\r\nPress 9 to EXIT");
   printf("\r\n\r\nValg: ");
}


struct _PURCHASEITEM* CrFindItem(struct _CASHREGISTER *pCashRegister, char *pszItemName) {
   struct _PURCHASEITEM* pItem = NULL;

   pItem = pCashRegister->pItemListHead;
   while (pItem != NULL) {
      if (_stricmp(pItem->szItemName, pszItemName) == 0) {
         pgdebug("Found item '%s'", pszItemName);
         break;
      }
      pItem = pItem->pNext;
   }
   return pItem;
}

float CrGetItemPriceFromItem(struct _PURCHASEITEM* pItem) {
   if (pItem == NULL) {
      pgerror("CrGetItemPriceFromItem called with a NULL pointer");
      return 0;
   }
   return pItem->fPrice;
}

void CrAddItem(struct _CASHREGISTER* pCashRegister, char* pszItemName, float fItemPrice, int iItemCount) {
   struct _PURCHASEITEM* pItem = NULL;

   pItem = CrFindItem(pCashRegister, pszItemName);
   if (pItem != NULL) {
      pgdebug("Item exists, increasing count: %s, %i", pszItemName, iItemCount);
      pItem->iCount += iItemCount;

      pCashRegister->pLastAdded = pItem;
      pCashRegister->iLastAddedCount = iItemCount;
   }
   else {
      pgdebug("Adding new item: %s, %f, %i", pszItemName, fItemPrice, iItemCount);
      pItem = malloc(sizeof(struct _PURCHASEITEM));
      if (pItem == NULL) {
         pgerror("malloc failed");
      }
      else {
         memset(pItem, 0, sizeof(struct _PURCHASEITEM));
         pItem->fPrice = fItemPrice;
         pItem->iCount = iItemCount;
         strncpy(pItem->szItemName, pszItemName, MAX_ITEMNAME - 1);

         pCashRegister->pLastAdded = pItem;
         pCashRegister->iLastAddedCount = iItemCount;

         if (pCashRegister->pItemListTail != NULL) {
            pItem->pPrev = pCashRegister->pItemListTail;
            pCashRegister->pItemListTail->pNext = pItem;
            pCashRegister->pItemListTail = pItem;
         }
         else {
            pCashRegister->pItemListHead = pItem;
            pCashRegister->pItemListTail = pItem;
         }
      
         pCashRegister->pLastAdded = pItem;
         pCashRegister->iLastAddedCount = iItemCount;
      }
   }
}

void CrDeleteItem(struct _CASHREGISTER* pCashRegister, struct _PURCHASEITEM* pItem) {
   if (pItem->pNext) {
      // Can set value to NULL, if so we just removed the first item (the head)
      pItem->pNext->pPrev = pItem->pPrev;
   }
   if (pItem->pPrev) {
      // Can set value to NULL, if so we just removed the last item (the tail)
      pItem->pPrev->pNext = pItem->pNext;
   }
   if (pCashRegister->pItemListHead == pItem) {
      // Can set value to NULL, if so we now have an empty list
      pCashRegister->pItemListHead = pCashRegister->pItemListHead->pNext;
   }
   if (pCashRegister->pItemListTail == pItem) {
      // Can set value to NULL, if so we now have an empty list
      pCashRegister->pItemListTail = pCashRegister->pItemListTail->pPrev;
   }
   free(pItem);
}

void CrDeleteLast(struct _CASHREGISTER* pCashRegister, struct _PURCHASEITEM* pLastAdded, int iLastAddedCount) {
   if (pLastAdded == NULL) {
      pgdebug("Last item not set, ignoring...");
   }
   else {
      if (pLastAdded->iCount != iLastAddedCount) {
         pgdebug("Reducing count of %s by %i (of %i)", pLastAdded->szItemName, iLastAddedCount, pLastAdded->iCount);
         pLastAdded->iCount -= iLastAddedCount;
      }
      else {
         CrDeleteItem(pCashRegister, pLastAdded);
      }
      pCashRegister->pLastAdded = NULL;
      pCashRegister->iLastAddedCount = 0;
   }
}

float CrCalculateSum(struct _CASHREGISTER* pCashRegister) {
   struct _PURCHASEITEM* pItem = NULL;
   float fSum = 0;

   pItem = pCashRegister->pItemListHead;
   while (pItem != NULL) {
      fSum += ((float)(pItem->iCount) * pItem->fPrice);
      pItem = pItem->pNext;
   }
   return fSum;
}

void CrPrintReceipt(struct _CASHREGISTER* pCashRegister) {
   struct _PURCHASEITEM* pItem = NULL;
   float fSum = 0;

   // Comment about grading: Extra credits could be earned here by making this receipt look more professional,
   // this function is quite simple and the minimum required... For instance having items with big differences
   // in name or very high amounts will offset the text too much for the tabulators to make it look pretty...
   // Drawing nice borders using - and | would be nitty-gritty work, but would ensure "extra credits" :-)

   printf("\r\n\r\nVARE\t\t\t\t\t\t\tTotal");


   pItem = pCashRegister->pItemListHead;
   while (pItem != NULL) {
      printf("\r\n%s\t\t\t%i * %f kr =\t\t%f", pItem->szItemName, pItem->iCount, pItem->fPrice, (float)(pItem->iCount) * pItem->fPrice);
      fSum += (pItem->iCount * pItem->fPrice);
      pItem = pItem->pNext;
   }
   printf("\r\n\r\n\t\t\t\t\t\tSum = \t%f", fSum);
}

/* End of file ------------------------------------------------------------------------------*/
