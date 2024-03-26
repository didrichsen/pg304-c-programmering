void *createNode(int iSize, char *psBuffer, int id){

    Node *pThis = NULL;
    pThis = malloc(sizeof (Node) + iSize);
    if(pThis != NULL){
        memset(pThis,0,sizeof (Node) + iSize);
        memcpy(pThis->cBuff,psBuffer,iSize);
        pThis->id = id;
    }

    return pThis;

}

//Adds node to head
int insertNode(List *pList, int iSize, char *psBuffer, int id){

    Node *pThis = createNode(iSize,psBuffer,id);

    if(pThis == NULL){
        //sddebug("Failed to create node.");
        return FAIL;
    }

    //List is empty
    if(pList->pHead == NULL){
        pThis->pNext = NULL;
        pThis->pPrevious = NULL;
        pList->pHead = pThis;
        pList->pTail = pThis;

        //List has existing nodes
    } else{
        pThis->pNext = pList->pHead;
        pList->pHead->pPrevious = pThis;
        pList->pHead = pThis;
        pThis->pPrevious = NULL;
    }

    return SUCCESS;

}

//Adds node to tail
int addNode(List *pList, int iSize, char *psBuffer, int id){

    Node *pThis = createNode(iSize,psBuffer,id);

    if(pThis == NULL){
        //sddebug("Failed to create node.");
        return FAIL;
    }

    if(pList->pTail == NULL){
        pThis->pNext = NULL;
        pThis->pPrevious = NULL;
        pList->pHead = pThis;
        pList->pTail = pThis;
    } else{
        pList->pTail->pNext = pThis;
        pThis->pPrevious = pList->pTail;
        pThis->pNext = NULL;
        pList->pTail = pThis;
    }

    return SUCCESS;
}

//Add to location
int insertAfter(List *pList, int iSize, char *psBuffer, int insertAfterId, int id){

    Node *pThis = createNode(iSize,psBuffer,id);

    if(pThis == NULL){
        //sddebug("Failed to create node.");
        return FAIL;
    }

    Node *pCurrent = pList->pHead;

    while (pCurrent != NULL){
        if(pCurrent->id == insertAfterId){
            pThis->pNext = pCurrent->pNext;
            pThis->pPrevious = pCurrent;

            if(pCurrent->pNext != NULL){
                pCurrent->pNext->pPrevious = pThis;
            } else{
                //Hvis current.next == NULL så vil pThis være siste node.
                pList->pTail = pThis;
            }

            pCurrent->pNext = pThis;

            return SUCCESS;
        }

        pCurrent = pCurrent->pNext;
    }

    //We didnt find the node to insert after
    free(pThis);
    return FAIL;
}

//Deletes head of list.
int deleteHead(List *pList){

    if(pList == NULL || pList->pHead == NULL){
        return FAIL;
    }

    Node *current = pList->pHead;

    if(current->pNext != NULL) {
        current->pNext->pPrevious = NULL;
    } else {
        //It was the last node in list.
        pList->pTail = NULL;
    }

    pList->pHead = current->pNext;

    free(current);

    return SUCCESS;

}

//Deletes tail
int deleteTail(List *pList){

    if(pList == NULL || pList->pTail == NULL){
        return FAIL;
    }

    Node *current = pList->pTail;

    if(current->pPrevious != NULL) {
        current->pPrevious->pNext = NULL;
    } else {
        //We need to update pointer since there was only one node in the list, or else dangling pointer.
        pList->pHead = NULL;
    }

    pList->pTail = current->pPrevious;

    free(current);

    return SUCCESS;

}

int deleteBasedOnID(List *pList, int id){

    if(pList == NULL || pList->pHead == NULL){
        return FAIL;
    }

    Node *current = pList->pHead;

    while (current != NULL){
        if(current->id == id){

            if(current->pPrevious == NULL){
                pList->pHead = current->pNext;
                if(current->pNext != NULL){
                    current->pNext->pPrevious = NULL;
                } else{
                    //If we are here. This was the only node and we need to update tail.
                    //Head will at this point already be NULL.
                    pList->pTail = NULL;
                }
            } else {
                current->pPrevious->pNext = current->pNext;

                if(current->pNext != NULL){
                    current->pNext->pPrevious = current->pPrevious;
                } else{
                    //If the current is the last node in the list
                    pList->pTail = current->pPrevious;
                }
            }

            free(current);

            return SUCCESS;

        }
        current = current->pNext;
    }

    return FAIL;

}

int deleteAll(List *pList){

    if(pList == NULL){
        return FAIL;
    }

    Node *pCurrent = pList->pHead;
    Node *pTemp;

    while (pCurrent != NULL){
        pTemp = pCurrent;
        pCurrent = pCurrent->pNext;
        free(pTemp);
    }

    pList->pHead = NULL;
    pList->pTail = NULL;

    return SUCCESS;

}

Node *findNode(List *pList, int id){

    if(pList == NULL){
        return NULL;
    }

    Node *pCurrent = pList->pHead;

    while (pCurrent != NULL){
        if(pCurrent->id == id){
            return pCurrent;
        }

        pCurrent = pCurrent->pNext;
    }

    return NULL;
}

int swapNodes(List *pList, Node *nodeOne, Node *nodeTwo){

    if(pList == NULL || nodeOne == NULL || nodeTwo == NULL || nodeOne == nodeTwo){
        return FAIL;
    }


    if(nodeOne->pNext == nodeTwo){ // nodeOne is immediately before nodeTwo
        nodeOne->pNext = nodeTwo->pNext;
        nodeTwo->pPrevious = nodeOne->pPrevious;

        if(nodeOne->pPrevious != NULL){
            nodeOne->pPrevious->pNext = nodeTwo;
        }
        if(nodeTwo->pNext != NULL){
            nodeTwo->pNext->pPrevious = nodeOne;
        }

        nodeTwo->pNext = nodeOne;
        nodeOne->pPrevious = nodeTwo;
    } else if(nodeTwo->pNext == nodeOne){ // nodeTwo is immediately before nodeOne
        nodeTwo->pNext = nodeOne->pNext;
        nodeOne->pPrevious = nodeTwo->pPrevious;

        if(nodeTwo->pPrevious != NULL){
            nodeTwo->pPrevious->pNext = nodeOne;
        }
        if(nodeOne->pNext != NULL){
            nodeOne->pNext->pPrevious = nodeTwo;
        }

        nodeOne->pNext = nodeTwo;
        nodeTwo->pPrevious = nodeOne;
    } else { // Nodes are not next to each other
        Node *temp = nodeOne->pNext;
        nodeOne->pNext = nodeTwo->pNext;
        nodeTwo->pNext = temp;

        temp = nodeOne->pPrevious;
        nodeOne->pPrevious = nodeTwo->pPrevious;
        nodeTwo->pPrevious = temp;

        if(nodeOne->pNext != NULL){
            nodeOne->pNext->pPrevious = nodeOne;
        }
        if(nodeTwo->pNext != NULL){
            nodeTwo->pNext->pPrevious = nodeTwo;
        }
        if(nodeOne->pPrevious != NULL){
            nodeOne->pPrevious->pNext = nodeOne;
        }
        if(nodeTwo->pPrevious != NULL){
            nodeTwo->pPrevious->pNext = nodeTwo;
        }
    }

    // Update the head and tail if needed
    if(pList->pHead == nodeOne){
        pList->pHead = nodeTwo;
    } else if(pList->pHead == nodeTwo){
        pList->pHead = nodeOne;
    }

    if(pList->pTail == nodeOne){
        pList->pTail = nodeTwo;
    } else if(pList->pTail == nodeTwo){
        pList->pTail = nodeOne;
    }

    return SUCCESS;
}

void printList(List *pList){

    if(pList == NULL){
        printf("List pointer is NULL.\n");
        return;
    }

    if(pList->pHead == NULL){
        printf("List is empty.\n");
        return;
    }

    Node *pCurrent = pList->pHead;
    while(pCurrent != NULL){
        printf("%s\n", pCurrent->cBuff);
        pCurrent = pCurrent->pNext;
    }
    printf("-----------------------------------\n");
}