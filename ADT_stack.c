#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    char* data;
    struct Node *next;
} NODE;

typedef struct Stack {
    int count;
    NODE* top;
} STACK;


STACK* initStack(STACK* stack) {
    stack = (STACK*)malloc(sizeof(STACK));
    stack->count = 0;
    stack->top = NULL;

    return stack;
}


NODE* createNode(char* data) {
    NODE* node = (NODE*)malloc(sizeof(NODE));
    node->data = strdup(data);
    node->next = NULL;

    return node;
}


void push(STACK* stack, char* data) {
    NODE* node = createNode(data);

    if (stack->top == NULL) { stack->top = node; }
    else {
        node->next = stack->top;
        stack->top = node;
    }

    stack->count++;
}


void pop(STACK* stack) {
    if (stack->top == NULL) { return; }
    else {
        NODE* node = stack->top->next;
        free(stack->top->data);
        free(stack->top);
        stack->top = node;
        stack->count--;
    }
}


NODE* peek(STACK* stack) {
    if (stack->top == NULL) { return NULL; }
    else {
        return stack->top;
    }
}


int size(STACK* stack) {
    return stack->count;
}


bool isEmpty(STACK* stack) {
    if (stack->count == 0) { return true; }
    else { return false; }
}


bool isFull(STACK* stack) {
    if (stack->count == INT_MAX) { return true; }
    else { return false; }
}


int main(void) {
    STACK* stack = initStack(stack);
    push(stack, "Lukas");
    push(stack, "Marko");
    push(stack, "Richard");
    pop(stack);
    pop(stack);
    pop(stack);
    push(stack, "Richard");
    pop(stack);
    pop(stack);
    NODE* node = peek(stack);


    return 0;
}

