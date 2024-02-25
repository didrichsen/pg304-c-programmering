/* KASSEAPPARAT.H header file -----------------------------------------------------------------

 Project     : Exam PG3401 H21 - Oppgave 3
 Author      : Bengt �stby
 Revision    : 1.0
 Description : Header file for cash register in Oppgave 3

--------------------------------------------------------------------------------------------*/

#ifndef __KASSEAPPARAT_H__
#define __KASSEAPPARAT_H__

#define MAX_ITEMNAME 32

struct _PURCHASEITEM {
   char szItemName[MAX_ITEMNAME];
   int iCount; // Keep signed to allow for returns
   float fPrice;
   struct _PURCHASEITEM *pNext;
   struct _PURCHASEITEM *pPrev;
};

struct _CASHREGISTER {
   struct _PURCHASEITEM *pItemListHead;
   struct _PURCHASEITEM* pItemListTail;
   // Instead of having a head and a tail pointer, and the last item having its pNext == NULL,
   // you could also have the list as a circle, and then just have a list pointer. None of
   // these are wrong, it is just two designs of a list. We use Head and Tail the most in
   // the lectures, but LIST_ENTRY is such a "circle list"...

   struct _PURCHASEITEM* pLastAdded;
   int iLastAddedCount;
};




void PrintCashRegisterScreen(void);
struct _PURCHASEITEM* CrFindItem(struct _CASHREGISTER* pCashRegister, char* pszItemName);
float CrGetItemPriceFromItem(struct _PURCHASEITEM* pItem);
void CrAddItem(struct _CASHREGISTER* pCashRegister, char* pszBuffer, float fItemPrice, int iItemCount);
void CrDeleteItem(struct _CASHREGISTER* pCashRegister, struct _PURCHASEITEM* pItem);
void CrDeleteLast(struct _CASHREGISTER* pCashRegister, struct _PURCHASEITEM* pLastAdded, int iLastAddedCount);
float CrCalculateSum(struct _CASHREGISTER* pCashRegister);
void CrPrintReceipt(struct _CASHREGISTER* pCashRegister);

#endif //__KASSEAPPARAT_H__
/* End of file ------------------------------------------------------------------------------*/