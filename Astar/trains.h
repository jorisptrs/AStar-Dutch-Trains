#include <stdlib.h> //allocs
#include <stdio.h> //scanf, printf
#include <string.h> //strcmp
#include <assert.h> //assert
#include <math.h> //sqrt

#ifndef TRAINS_H
#define TRAINS_H
#define INF 2147483647
#define N 11 // number of cities

typedef struct HeapElement {
    int city; // index of city in Graph.data[] and Graph.neighbourlist[], in order to retreive the neighbours etc.
    int d; // pseudo-distance (time in minutes)
    double h; // heuristic, the time it would take for a train to get between two cities in a straight line
} HeapElement;

/* we know exactly how many cities there will be so we include that in the definition */
typedef struct Heap {
    HeapElement array[N + 1];
    int front;
    int size;
} Heap;

typedef struct ListNode *ListPointer;

/* Edges will be represented by lists, where each list will represent the neighbours of one node */
struct ListNode {
    int node, weight;
    ListPointer next;
};

/* Edge is only used for constructing the graph */
typedef struct Edge {
    int start, end, weight;
} Edge;

typedef struct Graph {
    char *data[N]; // reference of city names and indicies
    double longitude[N];
    double latitude[N];
    int parent[N]; // array storing path
    ListPointer neighbourList[N]; // array storing lists that represent edges
} Graph;

// structFunctions.c prototypes
Heap makeHeap();
void swap(Heap *hp, int a, int b);
void upHeap(Heap *hp, int node);
void downHeap(Heap *hp, int node);
void enqueue(Heap *hp, int d, int city, double h);
HeapElement dequeue(Heap *hp);
Graph makeGraph();
void addNode(ListPointer *lp, int node, int weight);
void freeList(ListPointer lp);
ListPointer removeEdge(ListPointer lp, int node);
void freeGraph(Graph *G);

// aStar.c prototypes
int aStar(Graph *G, int start, int end);
void relaxation(HeapElement u, ListPointer li, Heap *toDo, Graph *G);

#endif