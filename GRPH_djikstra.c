#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6


int minDst(int dst[V], bool spt[V]) {
    int min = INT_MAX;
    int min_index = 0;

    for (int i = 0; i < V; i++) {
        if (spt[i] == false && dst[i] <= min) {
            min = dst[i];
            min_index = i;
        }
    }

    return min_index;
}


void printSolution(int dst[V]) {
    printf("Vertex\tDistance\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\n", i, dst[i]);
    }
}


void dijkstra(int graph[V][V]) {
    int dst[V];
    bool spt[V];

    for (int i = 0; i < V; i++) {
        dst[i] = INT_MAX;
        spt[i] = false;
    }

    dst[0] = 0;

    for (int i = 0; i < V - 1; i++) {
        int u = minDst(dst, spt);

        spt[i] = true;

        for (int j = 0; j < V; j++) {
            if (!spt[j] &&
                graph[u][j] &&
                dst[u] != INT_MAX &&
                dst[u] + graph[u][j] < dst[j]) {

                dst[j] = dst[u] + graph[u][j];
            }
        }
    }

    printSolution(dst);
}


int main(void) {
    int graph[V][V] = { { 0, 5, 4, 0, 2, 0},
                        { 5, 0, 8, 3, 0, 0},
                        { 4, 8, 0, 0, 5, 0},
                        { 0, 3, 0, 0, 6, 0},
                        { 2, 0, 5, 6, 0, 3},
                        { 0, 0, 0, 0, 3, 0} };


    dijkstra(graph);

    return 0;
}

