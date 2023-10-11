#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NODES 1000

// Define a queue data structure for BFS
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

// Define a graph structure
struct Graph {
    int numNodes;
    int adjacency[MAX_NODES][MAX_NODES];
};

// Queue functions

struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

bool isFull(struct Queue* queue) {
    return (queue->size == queue->capacity);
}

bool isEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

void enqueue(struct Queue* queue, int item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Graph functions

void initializeGraph(struct Graph* graph, int numNodes) {
    graph->numNodes = numNodes;
    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            graph->adjacency[i][j] = 0;
        }
    }
}

void addEdge(struct Graph* graph, int u, int v) {
    graph->adjacency[u][v] = graph->adjacency[v][u] = 1;
}

// Perform BFS traversal and find shortest distances
void BFS(struct Graph* graph, int startNode, int distances[]) {
    bool visited[MAX_NODES];
    for (int i = 0; i < graph->numNodes; ++i) {
        visited[i] = false;
        distances[i] = -1;
    }

    struct Queue* queue = createQueue(MAX_NODES);
    visited[startNode] = true;
    distances[startNode] = 0;
    enqueue(queue, startNode);

    while (!isEmpty(queue)) {
        int currentNode = dequeue(queue);
        printf("%d ", currentNode + 1);

        for (int i = 0; i < graph->numNodes; ++i) {
            if (graph->adjacency[currentNode][i] && !visited[i]) {
                visited[i] = true;
                distances[i] = distances[currentNode] + 2; // Edge weight is 2 units
                enqueue(queue, i);
            }
        }
    }
    printf("\n");
}

int main() {
    int numNodes, numEdges;
    scanf("%d %d", &numNodes, &numEdges);

    struct Graph graph;
    initializeGraph(&graph, numNodes);

    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(&graph, u - 1, v - 1); // Adjust node numbers to 0-based indexing
    }

    int startNode;
    scanf("%d", &startNode);
    startNode--; // Adjust startNode to 0-based indexing

    printf("BFS Traversal: ");
    int distances[MAX_NODES];
    BFS(&graph, startNode, distances);

    printf("Distance [");
    for (int i = 0; i < numNodes; ++i) {
        printf("%d", distances[i]);
        if (i < numNodes - 1)
            printf(" ");
    }
    printf("]\n");

    return 0;
}
