#ifndef C_PROGRAMMERING_MENU_APPLICATION_H
#define C_PROGRAMMERING_MENU_APPLICATION_H

typedef struct _Node{
    struct _Node *pNext;
    struct _Node *pPrevious;
    char cBuff[];
}Node;

typedef struct _List{
    struct _Node *pHead;
    struct _Node *pTail;
}List;

#define TRUE 0
#define FALSE 1

void printMenu();
int userInput(char firstOption, char lastOption);
void chooseOperation(int option);
void *createNode(int iSize, char *psBuffer);
int insertNode(List *pHead, int iSize, char *psBuffer);
int addNode(List *pHead, int iSize, char *psBuffer);

#endif //C_PROGRAMMERING_MENU_APPLICATION_H
