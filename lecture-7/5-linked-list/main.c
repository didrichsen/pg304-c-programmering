//
// Created by Simen Didrichsen on 04/03/2024.
//
#include "include/linked-list.h"
#include "include/sdlogger.h"
#include <stdlib.h>

int main(int argc, char* argv[]){

    NODE *head = NULL;

    insertAtHead(&head,30);
    insertAtHead(&head,40);
    insertAtHead(&head,50);

    insertAtTail(&head,100);

    freeNode(&head);

    printLinkedList(head);

    while (head != NULL){
        freeNode(&head);
    }

    return 0;
}
