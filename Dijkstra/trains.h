#include <stdlib.h> //allocs
#include <stdio.h> //scanf, printf
#include <string.h> //strcmp
#include <assert.h> //assert

#ifndef TRAINS_H
#define TRAINS_H
#define INF 2147483647
#define N 11 // number of cities

//heap
typedef struct HeapElement {
    int city; //index of city in Graph.data[] and Graph.neighbourlist[], in order to retreive the neighbours etc.
    int d; //pseudo-distance
} HeapElement;

// we know the exact numbe
typedef struct Heap {
    HeapElement array[N + 1];
    int front;
    int size;
} Heap;

//graph
typedef struct ListNode *ListPointer;

struct ListNode {
    int node, weight;
    ListPointer next;
};

typedef struct Edge {
    int start, end, weight;
} Edge;

typedef struct Graph {
    char *data[N]; // reference of city names and indicies
    int parent[N]; // array storing path
    ListPointer neighbourList[N]; // array storing lists that represent edges
} Graph;

// structFunctions.c prototypes
Heap makeHeap();
void swap(Heap *hp, int a, int b);
void upHeap(Heap *hp, int node);
void downHeap(Heap *hp, int node);
void enqueue(Heap *hp, int d, int city);
HeapElement dequeue(Heap *hp);
Graph makeGraph();
void addNode(ListPointer *lp, int node, int weight);
void freeList(ListPointer lp);
ListPointer removeEdge(ListPointer lp, int node);
void freeGraph(Graph *G);
int dijkstra(Graph *G, int start, int end);
void relaxation(HeapElement u, ListPointer li, Heap *toDo, Graph *G);

#endif