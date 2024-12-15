#include <stdio.h>
#include <stdlib.h>

struct Node {
    int dest;
    struct Node *next;
};

struct Graph {
    int vertices;
    struct Node **adjList;
    int *visited;
};

// Function to create the graph
struct Graph* createGraph(int vertices) {
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjList = (struct Node **)malloc(vertices * sizeof(struct Node *));
    graph->visited = (int *)malloc(vertices * sizeof(int));
    
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph *graph, int src, int dest) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// Function to sort adjacency list for each vertex
void sortAdjList(struct Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        struct Node *head = graph->adjList[i];
        int count = 0;
        
        // Count the number of adjacent nodes
        struct Node *temp = head;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        
        if (count <= 1) continue; // No need to sort
        
        // Extract adjacent vertices into an array
        int *adjVertices = (int *)malloc(count * sizeof(int));
        temp = head;
        for (int j = 0; j < count; j++) {
            adjVertices[j] = temp->dest;
            temp = temp->next;
        }
        
        // Sort the array
        for (int j = 0; j < count - 1; j++) {
            for (int k = 0; k < count - j - 1; k++) {
                if (adjVertices[k] > adjVertices[k + 1]) {
                    int swap = adjVertices[k];
                    adjVertices[k] = adjVertices[k + 1];
                    adjVertices[k + 1] = swap;
                }
            }
        }
        
        // Rebuild the adjacency list
        temp = head;
        for (int j = 0; j < count; j++) {
            temp->dest = adjVertices[j];
            temp = temp->next;
        }
        
        free(adjVertices);
    }
}

// BFS Traversal
void BFS(struct Graph *graph, int src) {
    int *queue = (int *)malloc(graph->vertices * sizeof(int));
    int front = 0, rear = 0, cur;

    queue[rear++] = src;
    graph->visited[src] = 1;

    while (front != rear) {
        cur = queue[front++];
        printf("%d ", cur);
        struct Node *temp = graph->adjList[cur];
        while (temp != NULL) {
            int adjVertex = temp->dest;
            if (!graph->visited[adjVertex]) {
                queue[rear++] = adjVertex;
                graph->visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }
    free(queue); // Free the allocated memory for the queue
}

// Main Function
int main() {
    int vertices, edges, src, dest;
    scanf("%d%d", &vertices, &edges);
    struct Graph *graph = createGraph(vertices);
    
    for (int i = 0; i < edges; i++) {
        scanf("%d%d", &src, &dest);
        addEdge(graph, src, dest);
    }
    
    sortAdjList(graph); // Sort adjacency lists for correct BFS traversal
    BFS(graph, 0);
    
    // Free allocated memory for the graph
    for (int i = 0; i < vertices; i++) {
        struct Node *temp = graph->adjList[i];
        while (temp != NULL) {
            struct Node *toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->adjList);
    free(graph->visited);
    free(graph);

    return 0;
}
