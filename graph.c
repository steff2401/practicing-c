#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 5
#define MAX_EDGES 10

typedef struct Node Node;

struct Node {
    int value, nNeighbours, neighbourSpace;
    Node **neighbours;
};

typedef struct Edge {
    Node *nodeA, *nodeB;
} Edge;

typedef struct Graph {
    Node* nodes[MAX_NODES];
    Edge* edges[MAX_EDGES];
    int nNodes;
} Graph;

Node* createNode(Graph *graph, int value);
void addNeighbour(Node *node, Node *neighbour);
void printGraph(Graph *graph);

int main(void) {
    // Initialize graph with member variables to NULL/0
    Graph graph = {0};

    // Create nodes
    Node* node1 = createNode(&graph, 1);
    Node* node2 = createNode(&graph, 2);
    Node* node3 = createNode(&graph, 3);
    Node* node4 = createNode(&graph, 4);

    // Add neighbours
    addNeighbour(node1, node2);
    addNeighbour(node2, node1);
    addNeighbour(node1, node3);
    addNeighbour(node2, node4);

    // Print out nodes and their neighbours
    printGraph(&graph);

    // Free memory
    for (int i = 0; i < graph.nNodes; i++) {
        free(graph.nodes[i]->neighbours);
        free(graph.nodes[i]);
    }

    return 0;
}

Node* createNode(Graph *graph, int value) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }

    node->value = value;
    node->nNeighbours = 0;
    node->neighbourSpace = 5; // initial capacity of 5 neighbours
    node->neighbours = malloc(sizeof(Node*)*node->neighbourSpace);
    if (node->neighbours == NULL) {
        printf("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }

    graph->nodes[graph->nNodes++] = node;

    return node;
}

// this function will only add neighbour for one node (the graph is directed)
void addNeighbour(Node *node, Node *neighbour) {
    if (node == NULL || neighbour == NULL) {
        printf("NullPointerException"); // guess which language I learnt before C?
        exit(EXIT_FAILURE);
    }

    if (node->nNeighbours >= node->neighbourSpace) { // if neighbour capacity full
        node->neighbourSpace *= 2; // double the capacity
        Node **np = realloc(node->neighbours, sizeof(Node*)*node->neighbourSpace);
        if (np == NULL) {
            printf("Reallocation of memory failed.");
            exit(EXIT_FAILURE);
        }
        node->neighbours = np;
    }

    node->neighbours[node->nNeighbours++] = neighbour; 
}

void printGraph(Graph *graph) {
    for (int i = 0; i < graph->nNodes; i++) {
        Node* node = graph->nodes[i];

        printf("Node %d has neighbours: ", node->value);
        for (int j = 0; j < node->nNeighbours; j++) {
            printf("%d ", node->neighbours[j]->value);
        }
        printf("\n");
    }
}