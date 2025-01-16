#include <stdio.h>
#include <stdlib.h>

int idx = 0;

typedef struct Node {
    int data;
    struct Node* next;
    int visited;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->visited = 0;
    return newNode;
}

Node** addToList(Node** adjList, int u, int v) {
    Node* node = createNode(v);
    if (adjList[u] == NULL) {
        adjList[u] = node;
        return adjList;
    }
    Node* temp = adjList[u];
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
    return adjList;
}

void freeAdjList(Node** adjList, int vertices) {
    for (int i = 0; i < vertices; i++) {
        Node* temp = adjList[i];
        while (temp != NULL) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(adjList);
}

Node* FindMin(Node *head) {
   Node *temp = head;
   Node *minNode = NULL;
   int min = temp->data;  // Set a high value initially
   while (temp != NULL) {
    if (!temp->visited && temp->data < min) {
        min = temp->data;
        minNode = temp;
    }
    temp = temp->next;
   }
   return minNode;
}

void DFS(Node** adjList, int u, int *STACK) {
    adjList[u]->visited = 1;
    STACK[idx++] = u;
    
    // Find the minimum unvisited neighboring node
    Node* minNeighbor = FindMin(adjList[u]);
    
    if (minNeighbor != NULL) {
        // If an unvisited neighbor with minimum value is found, visit it
        DFS(adjList, minNeighbor->data, STACK);
    } else {
        // If there are no unvisited neighbors, backtrack
        if (idx > 0) {
            idx--;  // Backtrack by removing the last node
        }
    }
}

int main() {
    int vertices, edges;
    int src[] = {0, 0, 0, 1, 1, 1, 2, 3, 4, 5};
    int dest[] = {1, 2, 3, 3, 4, 7, 4, 4, 5, 6};
    
    // Input for number of vertices and edges
    vertices = 8;
    edges = 10;
    int STACK[vertices];

    // Create adjacency list
    Node** adjList = (Node**)malloc(vertices * sizeof(Node*));
    for (int i = 0; i < vertices; i++) {
        adjList[i] = NULL;
    }

    // Add edges to the adjacency list
    for (int i = 0; i < edges; i++) {
        adjList = addToList(adjList, src[i], dest[i]);
    }

    // Start DFS from node 0
    DFS(adjList, 0, STACK);

    // Print visited nodes (DFS order)
    printf("DFS order: ");
    for (int i = 0; i < idx; i++) {
        printf("%d ", STACK[i]);
    }
    printf("\n");

    // Free memory
    freeAdjList(adjList, vertices);

    return 0;
}
