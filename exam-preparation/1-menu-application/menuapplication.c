#include "include/menuapplication.h"
#include <stdio.h>


int main(int argc, char* argv[]) {
    List myList;
    myList.pHead = NULL;
    myList.pTail = NULL;

    // Add nodes to the list
    addNode(&myList, 10, "First", 1);
    addNode(&myList, 10, "Second", 2);
    printList(&myList);
    //Expected output
    //First
    //Second
    insertNode(&myList, 10, "Third", 3);
    printList(&myList);
    //Expected output
    //Third
    //First
    //Second
    insertAfter(&myList, 10, "Fourth", 1, 4); // Insert after node with id 1
    printList(&myList);
    //Expected output
    //Third
    //First
    //Fourth
    //Second
    // Find a node
    Node* foundNode = findNode(&myList, 2);
    if (foundNode != NULL) {
        printf("Found node with id 2: %s\n", foundNode->cBuff);
    }

    // Swap nodes
    Node* nodeOne = findNode(&myList, 3);
    Node* nodeTwo = findNode(&myList, 4);
    if (nodeOne != NULL && nodeTwo != NULL) {
        swapNodes(&myList, nodeOne, nodeTwo);
    }

    printList(&myList);
    //Expected output
    //Fourth
    //First
    //Third
    //Second

    // Delete nodes
    deleteHead(&myList);
    deleteTail(&myList);
    deleteBasedOnID(&myList, 2);
    printList(&myList);
    //Expected output
    //First
    //Third

    // Delete all nodes
    deleteAll(&myList);
    printList(&myList);
    //Expected output
    //List is emtpy.

    return 0;
}