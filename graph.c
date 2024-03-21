#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 10

typedef struct Node Node;

struct Node {
    int value, nNeighbours, neighbourSpace;
    Node **neighbours;
    int *weights; // weight of edge to neighbour at corresponding index in **neighbours
};

typedef struct {
    Node* nodes[MAX_NODES];
    int nNodes;
} Graph;

Node* createNode(Graph *graph, int value);
void addEdge(Node *nodeFrom, Node *nodeTo, int weight);
void printGraph(Graph *graph);

int main(void) {
    // Initialize graph with member variables to NULL/0
    Graph graph = {0};

    // Create nodes
    Node* node1 = createNode(&graph, 1);
    Node* node2 = createNode(&graph, 2);
    Node* node3 = createNode(&graph, 3);
    Node* node4 = createNode(&graph, 4);

    // Add edges
    addEdge(node1, node2, 10);
    addEdge(node2, node1, 15);
    addEdge(node1, node3, 20);
    addEdge(node2, node4, 25);

    // Print out nodes and their neighbours
    printGraph(&graph);

    // Free memory
    for (int i = 0; i < graph.nNodes; i++) {
        free(graph.nodes[i]->neighbours);
        free(graph.nodes[i]->weights);
        free(graph.nodes[i]);
    }

    return 0;
}

Node* createNode(Graph *graph, int value) {
    if (graph->nNodes >= MAX_NODES) {
        printf("The graph is full.");
        exit(EXIT_FAILURE);
    }

    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }

    node->value = value;
    node->nNeighbours = 0;
    node->neighbourSpace = 5; // initial capacity of 5 neighbours
    node->neighbours = malloc(sizeof(Node*)*node->neighbourSpace);
    node->weights = malloc(sizeof(int)*node->neighbourSpace);
    if (node->neighbours == NULL || node->weights == NULL) {
        printf("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }

    graph->nodes[graph->nNodes++] = node;

    return node;
}

void addEdge(Node *nodeFrom, Node *nodeTo, int weight) {
    if (nodeFrom == NULL || nodeTo == NULL) {
        printf("NullPointerException"); // guess which language I learnt before C?
        exit(EXIT_FAILURE);
    }

    if (nodeFrom->nNeighbours >= nodeFrom->neighbourSpace) { // if neighbour capacity full
        nodeFrom->neighbourSpace *= 2; // double the capacity
        Node **newNeighbours = realloc(nodeFrom->neighbours, sizeof(Node*)*nodeFrom->neighbourSpace);
        int *newWeights = realloc(nodeFrom->weights, sizeof(int)*nodeFrom->neighbourSpace);
        if (newNeighbours == NULL || newWeights == NULL) {
            printf("Reallocation of memory failed.");
            exit(EXIT_FAILURE);
        }
        nodeFrom->neighbours = newNeighbours;
        nodeFrom->weights = newWeights;
    }

    nodeFrom->neighbours[nodeFrom->nNeighbours] = nodeTo;
    nodeFrom->weights[nodeFrom->nNeighbours++] = weight; 
}

void printGraph(Graph *graph) {
    for (int i = 0; i < graph->nNodes; i++) {
        Node* node = graph->nodes[i];

        printf("Node %d has neighbours: ", node->value);
        for (int j = 0; j < node->nNeighbours; j++) {
            printf("%d with weight %d, ", node->neighbours[j]->value, node->weights[j]);
        }
        printf("\n");
    }
}