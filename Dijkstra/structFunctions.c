#include "trains.h"

//To-do list - priority min queue using a heap (city, pseudo distance)
Heap makeHeap() {
    Heap h;
    h.front = 1;
    h.size = N + 1;
    return h;
}

void swap(Heap *hp, int a, int b) {
    HeapElement temp = hp->array[a]; // swap
    hp->array[a] = hp->array[b];
    hp->array[b] = temp;
}

void upHeap(Heap *hp, int node) {
    if (node == 1) {
        return;
    }
    if (hp->array[node / 2].d > hp->array[node].d) {
        swap(hp, node, node / 2);
        upHeap(hp, node / 2);
    }
}

void downHeap(Heap *hp, int node) {
    if (hp == NULL) {
        return;
    }
    int lc = node * 2;
    int rc = node * 2 + 1;
    if (lc >= hp->front) {
        return;
    }
    if (hp->array[lc].d < hp->array[node].d && (hp->front <= rc || hp->array[lc].d < hp->array[rc].d)) {
        swap(hp, lc, node);
        downHeap(hp, lc);
    } else if (hp->front > rc && hp->array[rc].d < hp->array[node].d) {
        swap(hp, rc, node);
        downHeap(hp, rc);
    }
}

void enqueue(Heap *hp, int d, int city) {
    hp->array[hp->front].d = d;
    hp->array[hp->front].city = city;
    upHeap(hp, hp->front);
    hp->front++;
}

HeapElement deHeap *hp) {
    HeapElement min;
    min = hp->array[1];
    hp->front--;
    hp->array[1] = hp->array[hp->front];
    downHeap(hp, 1);
    return min;
}

//Graph - array of links, data, costs)
void addNode(ListPointer *lp, int node, int weight) {
    ListPointer newList = malloc(sizeof(struct ListNode));
    assert(lp != NULL);
    newList->node = node;
    newList->next = *lp;
    newList->weight = weight;
    *lp = newList;
}

ListPointer removeEdge(ListPointer lp, int node) {
    if (lp == NULL) {
        return NULL;
    }
    if (lp->node == node) {
        ListPointer temp = lp->next;
        free(lp);
        return (temp);
    }
    lp->next = removeEdge(lp->next, node);
    return (lp);
}

Graph makeGraph() {
    Graph G;
    Edge edgeArray[] = {
        {0, 1, 51}, {0, 9, 26}, {1, 2, 89},
        {2, 6, 63}, {2, 8, 55}, {2, 9, 47},
        {3, 10, 50}, {4, 5, 34}, {4, 7, 50},
        {5, 7, 40}, {6, 8, 111}, {7, 10, 15},
        {8, 10, 77}, {9, 10, 51}
    };
    char *data[] = {
        "Amsterdam", "Den Haag", "Eindhoven",
        "Enschede", "Groningen", "Leeuwarden",
        "Maastricht", "Meppel", "Nijmegen",
        "Utrecht", "Zwolle"
    };
    memcpy(G.data, data, sizeof(data));
    int longitude = {

    }
    memcpy(G.longitude, data, sizeof(longitude));

    for (int i = 0; i < N; i++) {
        G.neighbourList[i] = NULL;
    }
    for (int i = 0; i < sizeof(edgeArray) / sizeof(edgeArray[0]); i++) {
        addNode(&(G.neighbourList[edgeArray[i].start]), edgeArray[i].end, edgeArray[i].weight);
        //add other direction too (undirected graph)
        addNode(&(G.neighbourList[edgeArray[i].end]), edgeArray[i].start, edgeArray[i].weight);
    }
    return G;
}

void freeList(ListPointer lp) {
    ListPointer lp1 = lp;
    while (lp != NULL) {
        lp1 = lp->next;
        free(lp);
        lp = lp1;
    }
}

void freeGraph(Graph *G) {
    int i;
    for (i = 0; i < 11; i++) {
        freeList(G->neighbourList[i]);
    }
}