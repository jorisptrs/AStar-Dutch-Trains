#include "trains.h"

// relaxation (maybe) updates the pseudo distance from a given city (u) to one of its neighbours
void relaxation(HeapElement u, ListPointer li, Heap *toDo, Graph *G) {
    int i = 1;
    //make i equal the place of li->node in toDo
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

/* aStar is a spin on Dijkstra's shortest path algorithm with a heuristic that,
 * int this case, factors in the straight line distance between the each city and the goal,
 * and looks at whether you are getting closer*/
int aStar(Graph *G, int start, int end) {
    Heap toDo = makeHeap();
    //assign INT_MAX to all heap nodes but the start
    for (int i = 0; i < N; i++) {
        if (i == start) {
            /* the 8015/192 is a coefficient that takes into account the circumference of the Earth, 
            the typical velocity of a Dutch domestic train and other conversion ratios to convert the
            angle between two cities into the time in minutes that a Dutch train would take to travel
            between two cites in a straight line */
            enqueue(&toDo, 0, i, sqrt((pow(G->longitude[i], 2) + pow(G->latitude[i], 2))) * 8015/192);
        } else {
            enqueue(&toDo, INF, i, sqrt((pow(G->longitude[i], 2) + pow(G->latitude[i], 2))) * 8015/192);
        }
    }
    HeapElement u;
    while (toDo.front > 1) {
        u = dequeue(&toDo);
        //check if goal reached
        if (u.city == end || u.d == INF) {
            return u.d;
        }
        ListPointer lcpy = G->neighbourList[u.city];
        //call relaxation on each city adjacent to u
        while (lcpy != NULL) {
            relaxation(u, lcpy, &toDo, G);
            lcpy = lcpy->next;
        }
    }
    return 0;
}
