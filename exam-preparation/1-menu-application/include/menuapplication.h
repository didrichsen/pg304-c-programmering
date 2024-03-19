#ifndef C_PROGRAMMERING_MENU_APPLICATION_H
#define C_PROGRAMMERING_MENU_APPLICATION_H

typedef struct _Node{
    struct _Node *pNext;
    struct _Node *pPrevious;
    int id;
    char cBuff[];
}Node;

typedef struct _List{
    struct _Node *pHead;
    struct _Node *pTail;
}List;

#define SUCCESS 0
#define FAIL 1

void printMenu();
int userInput(char firstOption, char lastOption);
void chooseOperation(int option);
void *createNode(int iSize, char *psBuffer, int id);
int insertNode(List *pHead, int iSize, char *psBuffer, int id);
int addNode(List *pHead, int iSize, char *psBuffer, int id);
int insertAfter(List *pList, int iSize, char *psBuffer, int insertAfterId, int id);
int deleteHead(List *pList);
int deleteTail(List *pList);
int swapNodes(List *pList, Node *nodeOne, Node *nodeTwo);
Node *findNode(List *pList, int id);
int deleteAll(List *pList);
int deleteBasedOnID(List *pList, int id);
void printList(List *pList);



#endif //C_PROGRAMMERING_MENU_APPLICATION_H
