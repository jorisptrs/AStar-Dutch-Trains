#include "trains.h"

//find the index of a city in the array G->data
int findIndex(char *str, char *array[N]) {
    for (int i = 0; i < N; i++) {
        if (!strcmp(str, array[i])) {
            return i;
        }
    }
    return 0;
}

void printGraph(Graph G) {
    for (int i = 0; i < N; i++) {
        printf("%d\t", i);
        ListPointer temp = G.neighbourList[i];
        while (temp != NULL) {
            printf("from %s to %s costs %d\n", G.data[i], G.data[temp->node], temp->weight);
            temp = temp->next;
        }
    }
}

void printJourney(Graph G, int start, int goal) {
    if (goal == start) {
        printf("%s\n", G.data[goal]);
        return;
    }
    printJourney(G, start, G.parent[goal]);
    printf("%s\n", G.data[goal]);
}

int main() {
    char start[10], goal[10];
    int n; //number of disruptions
    Graph G = makeGraph();
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf(" %[^'\n']s", start); //scanf also scanning ' '
        scanf(" %[^'\n']s", goal);
        G.neighbourList[findIndex(start, G.data)] =
        removeEdge(G.neighbourList[findIndex(start, G.data)], findIndex(goal, G.data));
        G.neighbourList[findIndex(goal, G.data)] =
        removeEdge(G.neighbourList[findIndex(goal, G.data)], findIndex(start, G.data));
    }
    int distance;
    while (1) {
        scanf(" %[^'\n']s", start);
        if (start[0] == '!') {
            break;
        }
        scanf(" %[^'\n']s", goal);
        distance = dijkstra(&G, findIndex(start, G.data), findIndex(goal, G.data));
        if (distance < INF) {
            printJourney(G, findIndex(start, G.data), findIndex(goal, G.data));
            printf("%d\n", distance);
        } else {
            printf("UNREACHABLE\n");
        }
    }
    freeGraph(&G);
    return 0;
}