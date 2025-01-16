#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int main() {
    int vertices, edges, x, y;

    printf("Enter number of Vertices and Edges: ");
    scanf("%d %d", &vertices, &edges);

    // Create adjacency list
    struct Node* adjList[vertices];
    for (int i = 0; i < vertices; i++) {
        adjList[i] = NULL;
    }

    printf("\nEnter Src and Dest:\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &x, &y);

        // Create a new node for the destination vertex
        struct Node* newNode = createNode(y);

        // Insert the node at the beginning of the adjacency list for the source vertex
        newNode->next = adjList[x];
        adjList[x] = newNode;
    }

    printf("\nAdjacency List:\n");
    for (int i = 0; i < vertices; i++) {
        printf("%d: ", i);
        struct Node* temp = adjList[i];
        while (temp != NULL) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }

    // Free the allocated memory
    for (int i = 0; i < vertices; i++) {
        struct Node* temp = adjList[i];
        while (temp != NULL) {
            struct Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }

    return 0;
}
