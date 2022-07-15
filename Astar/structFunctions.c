#include "trains.h"

// makeHeap creates an empty reverse heap of size 12, because we know we will have exactly 11 cities
Heap makeHeap() {
    Heap h;
    h.front = 1;
    h.size = N + 1;
    return h;
}

void swap(Heap *hp, int a, int b) {
    HeapElement temp = hp->array[a];
    hp->array[a] = hp->array[b];
    hp->array[b] = temp;
}

/* upHeap will be called to restore order to the heap after we change the pseudo-distance of a city
 * or enqueue a new heap element */
void upHeap(Heap *hp, int node) {
    if (node == 1) {
        return;
    }
    if (hp->array[node / 2].d + hp->array[node / 2].h > hp->array[node].d + hp->array[node].h) {
        swap(hp, node, node / 2);
        upHeap(hp, node / 2);
    }
}

/* downHeap restores order after dequeueing an element from our priority queue */
void downHeap(Heap *hp, int node) {
    if (hp == NULL) {
        return;
    }
    int lc = node * 2;
    int rc = node * 2 + 1;
    if (lc >= hp->front) {
        return;
    }
    if (hp->array[lc].d + hp->array[lc].h < hp->array[node].d + hp->array[node].h
    && (hp->front <= rc || hp->array[lc].d + hp->array[lc].h < hp->array[rc].d + hp->array[rc].h)) {
        swap(hp, lc, node);
        downHeap(hp, lc);
    } else if (hp->array[rc].d + hp->array[rc].h < hp->array[node].d + hp->array[node].h
    && hp->front > rc) {
        swap(hp, rc, node);
        downHeap(hp, rc);
    }
}

/* enqueue adds a new element to our heap/priority queue */
void enqueue(Heap *hp, int d, int city, double h) {
    hp->array[hp->front].d = d;
    hp->array[hp->front].city = city;
    hp->array[hp->front].h = h;
    upHeap(hp, hp->front);
    hp->front++;
}

/* dequeue removes and returns the first element of the priority queue */
HeapElement dequeue(Heap *hp) {
    HeapElement min;
    min = hp->array[1];
    hp->front--;
    hp->array[1] = hp->array[hp->front];
    downHeap(hp, 1);
    return min;
}

/* addNode adds a new node to a list of neighbours for a specific city, each node in the
 * list represents an edge */
void addNode(ListPointer *lp, int node, int weight) {
    ListPointer newList = malloc(sizeof(struct ListNode));
    assert(lp != NULL);
    newList->node = node;
    newList->next = *lp;
    newList->weight = weight;
    *lp = newList;
}

/* removeEdge removes a specific edge from a list of edges */
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

/* makeGraph creates the specific graph we need for the eleven Dutch cities in the exercise */
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
    double latitude[] = {
        52.3702, 52.0705, 51.4416,
        52.2215, 53.2194, 53.2012,
        50.8514, 52.6921, 51.8449,
        52.0907, 52.5168
    };
    double longitude[] = {
        4.8951, 4.3007, 5.4697,
        6.8937, 6.5665, 5.7999,
        5.6910, 6.1937, 5.8428,
        5.1214, 6.0830
    };
    memcpy(G.data, data, sizeof(data));
    memcpy(G.latitude, data, sizeof(latitude));
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

/* freeList frees a neghbour list */
void freeList(ListPointer lp) {
    ListPointer lp1 = lp;
    while (lp != NULL) {
        lp1 = lp->next;
        free(lp);
        lp = lp1;
    }
}

/* freeGraph calls the freeList function for each city in the graph */
void freeGraph(Graph *G) {
    int i;
    for (i = 0; i < 11; i++) {
        freeList(G->neighbourList[i]);
    }
}