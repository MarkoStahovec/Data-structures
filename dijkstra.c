#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define getParent(i) (((i)-1) / 2)
#define getLeft(i) (((i)*2) + 1)
#define getRight(i) (((i)*2) + 2)

#define INFINITY INT_MAX

/**
FIIT STU
Subject: Data structures and algorithms
Semester: SS 2020/2021
Author: Marko Stahovec

Assignment: 3
          : Dijkstra's path finding algorithm and binary heap
***/


typedef struct vertex {
    int32_t heap_index;
    int32_t X;
    int32_t Y;
    int32_t cost;
    int32_t length;
    struct vertex* prev;
} VERTEX;

typedef struct heap {
    int32_t size;
    VERTEX** vertex_array;
} HEAP;

typedef struct path {
    int32_t cost;
    int32_t length; // ???????????????????????????????????????

} PATH;


HEAP* getNewHeap();
void swap(HEAP* heap, int32_t x, int32_t y);
VERTEX* extractMinimum(HEAP* heap);
void extractCorrection(HEAP* heap);
void insertVertex(HEAP* heap, VERTEX* newVX);
void insertCorrection(HEAP* heap, int32_t index);
VERTEX* getNewVertex(int32_t index, int32_t cost);
void printMap(char** map, int32_t height, int32_t width);
void freeMap(VERTEX*** vertex_map, int height, int width);
void initializeMap(VERTEX*** vertex_map, char **char_map, int height, int width);
void updateVertexCost(HEAP* heap, char **char_map, VERTEX* old_VX, VERTEX* new_VX);
void calculateMapCost(VERTEX*** vertex_map, char **char_map, int32_t height, int32_t width, int32_t X_init_coor, int32_t Y_init_coor);


HEAP* getNewHeap() {
    HEAP* new_heap = malloc(sizeof(HEAP));

    new_heap->size = 0;
    new_heap->vertex_array = calloc(20, sizeof(VERTEX*));

    return new_heap;
}


void swap(HEAP* heap, int32_t x, int32_t y) {
    VERTEX* temp = heap->vertex_array[x];
    heap->vertex_array[x] = heap->vertex_array[y];
    heap->vertex_array[y] = temp;

    heap->vertex_array[x]->heap_index = x;
    heap->vertex_array[y]->heap_index = y;
}

VERTEX* extractMinimum(HEAP* heap) {
    if (heap->size == 0) {
        return NULL;
    }
    if (heap->size == 1) {
        heap->size = 0;
        heap->vertex_array[1] = NULL;
        return heap->vertex_array[0];
    }

    VERTEX* minimum = heap->vertex_array[0];
    heap->size--;
    extractCorrection(heap);

    return minimum;
}

void extractCorrection(HEAP* heap) {
    int32_t index = 0;

    heap->vertex_array[index]->heap_index = -1;
    heap->vertex_array[index] = heap->vertex_array[heap->size];
    heap->vertex_array[index]->heap_index = index;
    heap->vertex_array[heap->size] = NULL;

    if (heap->size == 1) {
        return;
    }

    if (heap->size == 2) {
        if (heap->vertex_array[0]->cost > heap->vertex_array[1]->cost) {
            swap(heap, 0, 1);
            return;
        }
        else return;
    }

    while(1) {
        if ((heap->vertex_array[index]->cost >= heap->vertex_array[getLeft(index)]->cost) || (heap->vertex_array[index]->cost >= heap->vertex_array[getRight(index)]->cost)) {
            if (heap->vertex_array[getRight(index)] != NULL) {
                if ((heap->vertex_array[getLeft(index)]->cost > heap->vertex_array[getRight(index)]->cost)) {
                    swap(heap, index, getRight(index));
                    index = getRight(index);
                }

                else  {
                    swap(heap, index, getLeft(index));
                    index = getLeft(index);
                }
            }
            else {
                swap(heap, index, getLeft(index));
                index = getLeft(index);
            }

            if (index*2 >= (heap->size)-1) break;

            //extractCorrection(heap);
        }
        else { break;}
    }
}


void insertVertex(HEAP* heap, VERTEX* newVX) {
    heap->vertex_array[heap->size] = newVX;
    heap->vertex_array[heap->size]->heap_index = heap->size;
    insertCorrection(heap, heap->size);
    heap->size++;
}


void insertCorrection(HEAP* heap, int32_t index) {
    if (index <= 1) {
        return;
    }
    while (heap->vertex_array[index]->cost < heap->vertex_array[getParent(index)]->cost) {
        swap(heap, index, getParent(index));
        index = getParent(index);
    }
}

VERTEX* getNewVertex(int32_t index, int32_t cost) {
    VERTEX* newVX = malloc(sizeof(VERTEX));

    newVX->heap_index = index;
    newVX->cost = cost;

    return newVX;
}


void printArray(HEAP* heap)
{
    for (int i = 0; i < heap->size; i++)
        printf("%d ", heap->vertex_array[i]->cost);

    printf("\n");
}

/*
int main(void) {
    HEAP* heap = getNewHeap();

    VERTEX* newVX = getNewVertex(heap->size, 10);
    insertVertex(heap, newVX);
    VERTEX* newVX1 = getNewVertex(heap->size, 4);
    insertVertex(heap, newVX1);
    VERTEX* newVX2 = getNewVertex(heap->size, 15);
    insertVertex(heap, newVX2);
    extractMinimum(heap);
    VERTEX* newVX3 = getNewVertex(heap->size, 20);
    insertVertex(heap, newVX3);
    VERTEX* newVX4 = getNewVertex(heap->size, 0);
    insertVertex(heap, newVX4);
    VERTEX* newVX5 = getNewVertex(heap->size, 30);
    insertVertex(heap, newVX5);

    extractMinimum(heap);
    extractMinimum(heap);
    extractMinimum(heap);



    VERTEX* newVX6 = getNewVertex(heap->size, 2);
    insertVertex(heap, newVX6);
    VERTEX* newVX7 = getNewVertex(heap->size, 4);
    insertVertex(heap, newVX7);
    VERTEX* newVX8 = getNewVertex(heap->size, -1);
    insertVertex(heap, newVX8);
    VERTEX* newVX9 = getNewVertex(heap->size, -3);
    insertVertex(heap, newVX9);


    printArray(heap);
    printf("%d", heap->size);

    return 0;
}*/

/*
 * -----------------------------------   DJIKSTRA SECTION   -----------------------------------
 */


void printMap(char** char_map, int32_t height, int32_t width) {
    printf("\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c ", char_map[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}


void printVertexMap(VERTEX*** vertex_map, int height, int width) {
    printf("\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d ", vertex_map[i][j]->cost);
        }
        printf("\n");
    }

    printf("\n");
}


void freeMap(VERTEX*** vertex_map, int height, int width) {

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            if (vertex_map[x][y] != NULL) {
                free(vertex_map[x][y]);
            }
        }

        free(vertex_map[x]);
    }

    free(vertex_map);
}


void initializeMap(VERTEX*** vertex_map, char **char_map, int width, int height) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (char_map[x][y] != 'N') {
                vertex_map[x][y]->heap_index = 0;
                vertex_map[x][y]->cost = INFINITY;
                vertex_map[x][y]->length = 0;
                vertex_map[x][y]->X = y;             // FIXME: possibly bug
                vertex_map[x][y]->Y = x;
                vertex_map[x][y]->prev = NULL;
            }
        }
    }
}


void updateVertexCost(HEAP* heap, char **char_map, VERTEX* old_VX, VERTEX* new_VX) {
    if (char_map[old_VX->Y][old_VX->X] == 'H') {
        if ((old_VX->cost + 2 < new_VX->cost) || (new_VX->cost == INFINITY)) {

            new_VX->cost = old_VX->cost + 2;
            new_VX->length = old_VX->length + 1;
            new_VX->prev = old_VX;
        }
    }
    else {
        if ((old_VX->cost + 1 < new_VX->cost) || (new_VX->cost == INFINITY)) {

            new_VX->cost = old_VX->cost + 1;
            new_VX->length = old_VX->length + 1;
            new_VX->prev = old_VX;
        }
    }

    if (new_VX->heap_index > 0) {
        insertCorrection(heap, new_VX->heap_index);
    }
    else {
        insertVertex(heap, new_VX);
    }
}


void calculateMapCost(VERTEX*** vertex_map, char **char_map, int32_t height, int32_t width, int32_t X_init_coor, int32_t Y_init_coor) {
    VERTEX* temp = vertex_map[Y_init_coor][X_init_coor];
    HEAP* heap = getNewHeap();


    if (char_map[Y_init_coor][X_init_coor] == 'N') {
        fprintf(stderr, "Intransitive obstacle was generated on starting coordinates");
        exit(0);
    }
    else if (char_map[Y_init_coor][X_init_coor] == 'H') {
        temp->cost = 2;
    }
    else {
        temp->cost = 1;
    }

    insertVertex(heap, temp);

    while (temp != NULL) {
        if ((temp->Y+1 < height) && vertex_map[temp->Y+1][temp->X]->heap_index >= 0) {
            if (char_map[temp->Y+1][temp->X] != 'N') {
                VERTEX* new_VX = vertex_map[temp->Y+1][temp->X];
                updateVertexCost(heap, char_map, temp, new_VX);
            }

        }
        if ((temp->Y-1 >= 0) && (vertex_map[temp->Y-1][temp->X]->heap_index >= 0)) {
            if (char_map[temp->Y-1][temp->X] != 'N') {
                VERTEX* new_VX = vertex_map[temp->Y-1][temp->X];
                updateVertexCost(heap, char_map, temp, new_VX);
            }

        }
        if ((temp->X+1 < width) && vertex_map[temp->Y][temp->X+1]->heap_index >= 0) {
            if (char_map[temp->Y][temp->X+1] != 'N') {
                VERTEX* new_VX = vertex_map[temp->Y][temp->X+1];
                updateVertexCost(heap, char_map, temp, new_VX);
            }

        }
        if ((temp->X-1 >= 0) && (vertex_map[temp->Y][temp->X-1]->heap_index >= 0)) {
            if (char_map[temp->Y][temp->X-1] != 'N') {
                VERTEX* new_VX = vertex_map[temp->Y][temp->X-1];
                updateVertexCost(heap, char_map, temp, new_VX);
            }

        }

        temp = extractMinimum(heap);
    }

    free(heap->vertex_array);
    free(heap);
}


PATH* createPath(char** char_map, VERTEX* c_vertex) {
    PATH* c_path = malloc(sizeof(PATH));
    if (c_vertex->prev == NULL) {
        return NULL;
    }

    return c_path;
}


int* zachran_princezne(char** mapa, int n, int m, int t, int* dlzka_cesty) {
    int32_t X_dragon, Y_dragon;
    PATH* best_path = (PATH*) malloc(sizeof(PATH));

    VERTEX*** vertex_map = (VERTEX***)malloc(n*sizeof(VERTEX**));

    for (int x = 0; x < n; x++) {
        vertex_map[x] = (VERTEX**)malloc(m*sizeof(VERTEX*));
        for (int y = 0; y < m; y++) {
            if (mapa[x][y] == 'D') {
                X_dragon = y;
                Y_dragon = x;
            }

            best_path = createPath(mapa, vertex_map[Y_dragon][X_dragon]);
            vertex_map[x][y] = (VERTEX*)malloc(sizeof(VERTEX));
        }
    }

    initializeMap(vertex_map, mapa, n, m);
    calculateMapCost(vertex_map, mapa, n, m, 0, 0);
    printVertexMap(vertex_map, n, m);


    freeMap(vertex_map, n, m);

    return dlzka_cesty;
}



int main() {
    char buff[2]; // this buffer will serve as initial input as to which function needs to be run
    FILE* map_file;
    int32_t n, m, time = 0;
    char** char_map;

    int* final_path;
    int32_t final_path_length;

    printf("r - run the program\nq - quit\n-----------------------\n");
    do { // do-while cycle to ensure that program keeps running
        //printf("r - run the program\nq - quit\n-----------------------\n");

        fgets(buff, 2, stdin); // loads input from buffer
        switch(buff[0]) { // function is determined by the first char in buffer
            case 'r':
                map_file = fopen("smallmap.txt", "r");
                fscanf(map_file, "%d %d %d\n", &n, &m, &time);

                char_map = (char**)malloc(n*sizeof(char*));
                for (int x = 0; x < n; x++) {
                    char_map[x] = (char*)malloc(m*sizeof(char));
                    for (int y = 0; y < m; y++) {
                        fscanf(map_file, "%c", &(char_map[x][y]));

                        while ((char_map[x][y] != 'C') &&
                        (char_map[x][y] != 'D') &&
                        (char_map[x][y] != 'P') &&
                        (char_map[x][y] != 'N') &&
                        (char_map[x][y] != 'H')) {
                            fscanf(map_file, "%c" ,&(char_map[x][y]));
                        }
                    }
                }

                fclose(map_file);
                printf("------- Initial map -------\n");
                printMap(char_map, n, m);
                printf("------- Solution -------\n");
                final_path = zachran_princezne(char_map, n, m, time, &final_path_length);

                break;
            default:
                break;
        }
    } while(buff[0] != 'q'); // q terminates program


    return 0;
}