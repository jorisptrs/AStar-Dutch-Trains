#include "trains.h"

void relaxation(HeapElement u, ListPointer li, Heap *toDo, Graph *G) {
    int i = 1;
    while (i < toDo->front && li->node != toDo->array[i].city) {
        i++;
    }
    if (G->neighbourList[li->node] == NULL || i == toDo->front) {
        return;
    }
    if (u.d + li->weight < toDo->array[i].d) {
        toDo->array[i].d = u.d + li->weight;
        G->parent[li->node] = u.city;
        upHeap(toDo, i);
    }
}

int dijkstra(Graph *G, int start, int end) {
    Heap toDo = makeHeap();
    //assign INT_MAX to all heap nodes but the start
    for (int i = 0; i < N; i++) {
        if (i == start) {
            enqueue(&toDo, 0, i);
        } else {
            enqueue(&toDo, INF, i);
        }
    }
    HeapElement u;
    while (toDo.front > 1) {
        u = dequeue(&toDo);
        if (u.city == end || u.d == INF) {
            return u.d;
        }
        ListPointer lcpy = G->neighbourList[u.city];
        while (lcpy != NULL) {
            relaxation(u, lcpy, &toDo, G);
            lcpy = lcpy->next;
        }
    }
    return 0;
}
