#ifndef ACTOR_H
#define ACTOR_H

// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants for success and error
#define SUCCESS 0
#define ERROR (-1)

// Define the ACTOR structure
typedef struct ACTOR {
    char *pszFirstName;
    char *pszLastName;
    struct ACTOR *pNext;
} ACTOR;

// Define the ACTORS_LIST structure
typedef struct ACTORS_LIST {
    ACTOR *pHead;
} ACTORS_LIST;

#define MAX_NAME_SIZE 128

// Function prototypes
int DeleteActorList(ACTORS_LIST *pList);
int AddActors(ACTORS_LIST *pList, char *szFirstName, char *szLastName);

#endif // ACTOR_H