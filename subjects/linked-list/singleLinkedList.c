#include<stdio.h>
#include<stdlib.h>

// Define the structure for a node
typedef struct _node {
    int iData;            // Data stored in the node
    struct _node * next;  // Pointer to the next node
} node;

// Function prototype for inserting a new node at the start of the list
void insertStart(node **head, int data);

int main(int argc, char* argv[]) {
    node *head = NULL; // Initialize an empty linked list

    // Insert some elements at the beginning of the list
    insertStart(&head, 100);
    insertStart(&head, 50);
    insertStart(&head, 25);
    insertStart(&head, 10);

    // Print the linked list
    printf("Linked list elements: ");
    node *current = head;
    while (current != NULL) {
        printf("%d ", current->iData); // Print current node's data
        current = current->next;       // Move to the next node
    }
    printf("\n");

    // Free memory
    current = head;
    while (current != NULL) {
        node *temp = current;       // Store the current node in a temporary variable
        current = current->next;    // Move to the next node before freeing the current one
        free(temp);                 // Free memory for the current node
    }

    return 0;
}

// Function to insert a new node at the start of the list
void insertStart(node **head, int data) {
    // Allocate memory for a new node
    node *newHead = (node*) malloc(sizeof(node));

    // Check if memory allocation was successful
    if (newHead == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE); // Terminate the program
    }

    // Initialize the new node with the provided data
    newHead->iData = data;
    // Make the new node point to the current head of the list
    newHead->next = *head;
    // Update the head pointer to point to the new node
    *head = newHead;

    // Print a message indicating the insertion
    printf("\n%d Inserted\n", newHead->iData);
}
