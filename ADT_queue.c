#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct Node {
    char* data;
    struct Node* next;
} NODE;


typedef struct Queue {
    NODE* front;
    NODE* rear;
    int count;
} QUEUE;


QUEUE* initQueue() {
    QUEUE* queue = (QUEUE*)malloc(sizeof(QUEUE));
    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;

    return queue;
}


NODE* createNode(char* data) {
    NODE* node = (NODE*)malloc(sizeof(NODE));
    node->data = strdup(data);
    node->next = NULL;

    return node;
}


void enqueue(QUEUE* queue, char* data) {
    NODE* node = createNode(data);
    if ((queue->front == NULL) && (queue->rear == NULL)) {
        queue->front = node;
        queue->rear = node;
        queue->count = 1;
    }
    else {
        queue->rear->next = node;
        queue->rear = node;
        queue->count++;
    }
}


void dequeue(QUEUE* queue) {
    if (queue->front == NULL) { return; }
    else {
        NODE* temp = queue->front;
        queue->front = queue->front->next;

        if (queue->front == NULL) {
            queue->rear = NULL;
        }

        queue->count--;
        free(temp->data);
        free(temp);
    }
}


NODE* peek(QUEUE* queue) {
    if (queue->front != NULL) {
        return queue->front;
    }
    return NULL;
}


int size(QUEUE* queue) {
    return queue->count;
}


bool isEmpty(QUEUE* queue) {
    if ((queue->front == NULL) && (queue->rear == NULL)) { return true; }
    return false;
}


bool isFull(QUEUE* queue) {
    if (queue->count == INT_MAX) { return true; }
    return false;
}


int main(void) {
    QUEUE* queue = initQueue();
    enqueue(queue, "Marko");
    enqueue(queue, "Richard");
    enqueue(queue, "Lukas");
    dequeue(queue);
    if (!isEmpty(queue)) { enqueue(queue, "Adrian");};
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);

    return 0;
}

