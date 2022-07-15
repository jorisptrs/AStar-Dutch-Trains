#include "trains.h"

// find the index of a city in the array G->data
int findIndex(char *str, char *array[N]) {
    for (int i = 0; i < N; i++) {
        if (!strcmp(str, array[i])) {
            return i;
        }
    }
    return 0;
}

// printJourney prints the path from start to goal by recursively being called on the parents of the cities
void printJourney(Graph G, int start, int goal) {
    if (goal == start) {
        printf("%s\n", G.data[goal]);
        return;
    }
    printJourney(G, start, G.parent[goal]);
    printf("%s\n", G.data[goal]);
}

/* creates a dialogue with the user and calls the functions from structFunctions.c and AStar.c when needed.
 * It first calls for the removal of n edges and then calls for computing the shortest path */
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
        // remove edge in both ways (we have an undirected graph)
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
        distance = aStar(&G, findIndex(start, G.data), findIndex(goal, G.data));
        // print the journey if a plausible distance was found
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