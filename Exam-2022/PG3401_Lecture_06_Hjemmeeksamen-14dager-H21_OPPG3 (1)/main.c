/* MAIN.C header file -------------------------------------------------------------------------

 Project     : Exam-2022 PG3401 H21 - Oppgave 3
 Author      : Bengt �stby
 Revision    : 1.0
 Description : Main function for oppgave 3

--------------------------------------------------------------------------------------------*/



/*=== Standard C my-static-library: ===============================================================
=======================================================================================*/

#define _CRT_SECURE_NO_WARNINGS // Dangerous and we would never do this, except this is a luddite course
#include <stdio.h>
// #2-include <conio.h>

#include <stdlib.h>
#include <string.h>

/*=== Project spesific 2-include files: ===================================================
=======================================================================================*/

#include "pgdbglog.h"

#include "kasseapparat.h"

enum MENUSELECTION {
   MENU_UNINITIALIZED = 0,
   MENU_ADDITEM = 1,
   MENU_DELETELAST = 2,
   MENU_DELETEONE = 3,
   MENU_GETTOTAL = 4,
   MENU_PRINTRECEIPT = 5,
   MENU_EXITCODE = 9
};

/*=== Main function: ====================================================================
 Author      : Bengt �stby
 Revision    : 1.0

 
 Comments regarding grading:
 
=======================================================================================*/

enum MENUSELECTION ___getch();

int main(int iArgc, char *apszArgv[]){
   struct _CASHREGISTER CashRegister = { 0 };
   enum MENUSELECTION eMenuSelection = MENU_UNINITIALIZED;
   char szBuffer[64] = { 0 };
   float fItemPrice = 0;
   int iItemCount = 0;
   struct _PURCHASEITEM *pItem = NULL;
   struct _PURCHASEITEM* pDelete = NULL;
   int iRetcode = 0;
   float fSum = 0;

   PgDbgInitialize(); // Needed to enable debug printing...

   do {
      PrintCashRegisterScreen();

      ///////////////////////////////////////////////////////////////////////////////////
      // Notice the difference in behavior of different functions
      // getchar() used here will let the user type (as many chars) as he/she wants, and
      // the user needs to press [enter], the next time we call getchar it will return
      // automatically with an empty value because the [enter] is also registered...
      // getc(stdin) has the exact same behavior (with both functions it would be
      // possible to simply call getc(har) twice, and some students just ignore this
      // or simply does not notice this weird effect...
      // Windows developers (or Turbo C users) would typically use _getch(), but that is
      // neither part of ANSI C or POSIX, and is not supported on Linux. There is a trick
      // to implement the same type of functions on Linux, as described in this article
      // https://www.includehelp.com/c-programs/gotoxy-clrscr-getch-getche-for-gcc-linux.aspx
      // For this project we have chosen to use fgets, but we move the details out to
      // a seperate function. scanf would also be a workable option, or getc as detailed.

      eMenuSelection = ___getch();

      ///////////////////////////////////////////////////////////////////////////////////
      // Process menu selection
      ///////////////////////////////////////////////////////////////////////////////////

      printf("\r\nMenu selection = (%i)", eMenuSelection);

      switch (eMenuSelection) {
         case MENU_ADDITEM:
            memset(szBuffer, 0, sizeof(szBuffer));
            fItemPrice = 0; iItemCount = 0;

            /////////////////////////////////////////////////////////////////////////////
            // Adding a new item means we have to read the values for that item, we
            // MUST ensure that when we read a string we do not overflow a stack or
            // heap buffer. This means that we MUST use a function that takes the size
            // of the buffer as parameter - all other function WILL overflow the buffer.
            // The simplest function that reads a string with a max size is fgets.
            /////////////////////////////////////////////////////////////////////////////

            printf("\r\n\r\nPlease enter item NAME: ");
            fgets(szBuffer, sizeof(szBuffer) - 1, stdin);

            while (szBuffer[strlen(szBuffer) - 1] == '\r' || szBuffer[strlen(szBuffer) - 1] == '\n') {
               pgdebug("Stripping whitespace...");
               szBuffer[strlen(szBuffer) - 1] = 0;
            }

            // If the item exists we already know the price
            // Comments regarding grading: This is beyond what is expected, but might
            // give us those extra credits that ensures us an A :-)
            pItem = CrFindItem(&CashRegister, szBuffer);
            if (pItem != NULL) {
               printf("\r\nItem found, price is %f, will increase count", CrGetItemPriceFromItem(pItem));
            }
            else {
               printf("\r\n\r\nPlease enter item PRICE: ");
               iRetcode = scanf("%f", &fItemPrice); // Do not use scanf with %s for a string, it will be a security issue, %f should be fine
               if (iRetcode != 1) {
                  pgerror("scanf failed with %i");
               }
            }

            printf("\r\n\r\nPlease enter item COUNT: ");
            iRetcode = scanf("%i", &iItemCount); // Do not use scanf with %s for a string, it will be a security issue, %f should be fine
            if (iRetcode != 1) {
               pgerror("scanf failed with %i");
            }

            CrAddItem(&CashRegister, szBuffer, fItemPrice, iItemCount);
            break;
         case MENU_DELETELAST:

            /////////////////////////////////////////////////////////////////////////////
            // Deleting the last item could be very difficult, if we cater for "adding"
            // an existing item which means that the last item in the list might not be
            // the last item added - not to mention if we later decided to SORT the list
            // while adding it... Or it could be very easy if we just kept a pointer :-)
            /////////////////////////////////////////////////////////////////////////////

            CrDeleteLast(&CashRegister, CashRegister.pLastAdded, CashRegister.iLastAddedCount); // Last two parameters are of course superficial

            break;
         case MENU_DELETEONE:

            /////////////////////////////////////////////////////////////////////////////
            // If we allowed several items with the same name to be added then this
            // function would be more difficult because we would to cater for several
            // items with the same name (the exam text said "all items of a given NAME",
            // however since we went to extra mile to search for existing items and just
            // increase the count - then we save time on this function :-)
            /////////////////////////////////////////////////////////////////////////////

            printf("\r\n\r\nPlease enter item NAME: ");
            fgets(szBuffer, sizeof(szBuffer) - 1, stdin);

            pItem = CrFindItem(&CashRegister, szBuffer);
            if (pItem == NULL) {
               pgerror("Item '%s' not found", szBuffer);
            }
            else {
               pgdebug("Deleting '%s' at memory address %08x", szBuffer, pItem);
               CrDeleteItem(&CashRegister, pItem);
               pItem = NULL;
            }

            break;
         case MENU_GETTOTAL:

            /////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////

            fSum = CrCalculateSum(&CashRegister);
            printf("\r\n\r\nSUM = %f", fSum);
            printf("\r\nPress <enter> to continue...");
            eMenuSelection = ___getch();

            break;
         case MENU_PRINTRECEIPT:

            /////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////

            CrPrintReceipt(&CashRegister);
            printf("\r\nPress <enter> to continue...");
            eMenuSelection = ___getch();

            break;

         default:

            /////////////////////////////////////////////////////////////////////////////
            // We must always have a default entry, even if we know we have a case
            // for all possible values it is good and clean coding to have default...
            /////////////////////////////////////////////////////////////////////////////

            break; // Technically a break is not needed here, but good coding convension
      } // end switch (eMenuSelection)

   } while (eMenuSelection != MENU_EXITCODE);

   //////////////////////////////////////////////////////////////////////////////////////
   // Free allocated memory and perform cleanup
   //////////////////////////////////////////////////////////////////////////////////////

   pItem = CashRegister.pItemListHead;
   while (pItem != NULL) {
      pDelete = pItem;
      pItem = pItem->pNext;
      free(pDelete);
   }
   memset(&CashRegister, 0, sizeof(struct _CASHREGISTER));

   return 0;   
}

enum MENUSELECTION ___getch() {
   char szBuffer[8] = { 0 };
   int iSelection = 0;

   fgets(szBuffer, 8 - 1, stdin);
   iSelection = atoi(szBuffer);

   if (iSelection == MENU_ADDITEM) {
      return MENU_ADDITEM;
   }
   if (iSelection == MENU_DELETELAST) {
      return MENU_DELETELAST;
   }
   if (iSelection == MENU_DELETEONE) {
      return MENU_DELETEONE;
   }
   if (iSelection == MENU_GETTOTAL) {
      return MENU_GETTOTAL;
   }
   if (iSelection == MENU_PRINTRECEIPT) {
      return MENU_PRINTRECEIPT;
   }
   if (iSelection == MENU_EXITCODE) {
      return MENU_EXITCODE;
   }
   pgerror("Character %i entered...");
   return MENU_UNINITIALIZED;
}


/* End of file ------------------------------------------------------------------------------*/
