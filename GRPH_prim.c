#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6


int minKey(int key[], bool mst[]) {

    int min = INT_MAX, min_index;

    for (int i = 0; i < V; i++) {
        if (mst[i] == false && key[i] < min)
            min = key[i], min_index = i;
    }

    return min_index;
}

void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t %d\n", parent[i], i, graph[i][parent[i]]);
    }
}


void primMST(int graph[V][V]) {
    int parent[V];
    int key[V];
    bool mst[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mst[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < V-1; i++) {
        int u = minKey(key, mst);

        mst[u] = true;

        for (int j = 0; j < V; j++) {
            if (graph[u][j] &&
                mst[j] == false &&
                graph[u][j] < key[j]) {

                parent[j] = u;
                key[j] = graph[u][j];
            }
        }
    }

    printMST(parent, graph);
}


int main(void) {

    int graph[V][V] = { { 0, 5, 4, 0, 2, 0},
                      { 5, 0, 8, 3, 0, 0},
                      { 4, 8, 0, 0, 5, 0},
                      { 0, 3, 0, 0, 6, 0},
                      { 2, 0, 5, 6, 0, 3},
                      { 0, 0, 0, 0, 3, 0} };


    primMST(graph);

    return 0;
}

