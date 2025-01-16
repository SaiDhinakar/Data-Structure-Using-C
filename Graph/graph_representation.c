#include <stdio.h>
#include <stdlib.h>

struct Node{
    int dest;
    struct Node* next;
};

struct Graph{
    int vertices;
    struct Node** adjList;
    int *visited;
};

struct Graph *createGraph(int vertices){
    struct Graph *graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjList = (struct Node**)malloc(vertices * sizeof(struct Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for(int i=0; i<vertices; i++){
        graph->adjList[i] = NULL;
        graph->visited[i]=0;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Add reverse edge for undirected graph
    /*
    newNode = malloc(sizeof(struct Node));
    newNode->dest = src;
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
    */
}

void BFS(struct Graph* graph, int src){
    int *queue = (int*) malloc (graph->vertices * sizeof(int));
    int front = 0, rear = 0;

    printf("BFS Traversal : ");
    queue[rear++] = src;
    graph->visited[src] = 1;

    while(front != rear){
        int cur = queue[front++];
        printf("%d ", cur);

        struct Node* temp = graph->adjList[cur];
        while(temp != NULL){
            int adjVertex = temp->dest;
            if (!graph->visited[adjVertex]){
                queue[rear++] = adjVertex;
                graph->visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

void DFS(struct Graph* graph, int vertex){
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* temp = graph->adjList[vertex];
    while (temp)
    {
        int adjVertex = temp->dest;
        if (!graph->visited[adjVertex]){
            DFS(graph, adjVertex);
        }
        temp = temp->next;
    }   
}

int main(){
    struct Graph* graph = createGraph(11);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    
    printf("Graph Traversal :\n");

    BFS(graph, 0);
    printf("\n");

    for(int i=0; i<6; i++)
        graph->visited[i] = 0;
    
    printf("DFS Traversal : ");
    DFS(graph, 0);
    printf("\n");
}