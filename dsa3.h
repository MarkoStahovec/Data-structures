#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>


#define TRUE 1
#define FALSE 0
#define getMax(a, b) (((a) > (b)) ? (a) : (b))

#define getParent(i) (((i)-1) / 2) // computes index in non-reduced diagram of vertex' parent
#define getLeft(i) (((i)*2) + 1) // computes index in non-reduced diagram of a left successor
#define getRight(i) (((i)*2) + 2) // computes index in non-reduced diagram of a right successor


/**
FIIT STU
Subject: Data structures and algorithms
Semester: SS 2020/2021
Author: Marko Stahovec

Assignment: 3
          : Binary decision diagram
***/

typedef unsigned int uint;

typedef struct vertex {
    char* data;
    int index;
    int depth;
    struct vertex* left;
    struct vertex* right;
    struct vertex* parent;
    struct vertex* next;
    struct vertex* prev;
} VERTEX;


typedef struct binary_decision_diagram {
    uint var_count;
    uint size;
    VERTEX* root;
    VERTEX* zero_leaf;
    VERTEX* one_leaf;
    VERTEX* last;
} BDD;


typedef struct boolean_function {
    char* vector;
} BF;


BDD* BDD_create(BF* bfunkcia);
int BDD_reduce(BDD* bdd);
char BDD_use(BDD* bdd, char* vstupy);
int is2Power(int number);
int checkVector(char* vector);
VERTEX* createVertex(char* data);
void createDiagram(int vector_length, VERTEX* root);
char* generateRandomVector();
char* generateSpecificVector(int var_count);
char* randomVector(int var_count);
BDD* mergeEquivalentLeafs(BDD* bdd);
void mergeIsomorphicNodes(BDD* bdd, VERTEX* root);
void merge(BDD* bdd, VERTEX* root);
void eliminateRedundantNodes(BDD* bdd, VERTEX* root);
void updateDepth(VERTEX* currentVX);
void mergeIsomorphic(BDD* bdd, int cycle);
void updateIndexing(BDD* bdd, VERTEX* root);
void createConnections(BDD* bdd, VERTEX** vertexArray);
VERTEX** traverseTree(BDD* bdd, VERTEX* root, VERTEX** vertexArray);
VERTEX** createVertexArray(BDD* bdd);
void updateSize(BDD* bdd, VERTEX* root);

// checks if a given number is power of 2
int is2Power(int number) {
    if (number == 0)
        return FALSE;

    return (ceil(log2(number)) == floor(log2(number)));
}

// checks if vector is made of zeros and ones only
int checkVector(char* vector) {
    for (int i = 0; i < strlen(vector); i++) {
        if (vector[i] != '0' && vector[i] != '1') {
            return FALSE;
        }
    }

    return TRUE;
}

// generates random vector
char* generateRandomVector() {
    int var_count = ((rand()) % 4) + 1; // int var_count = ((rand()) % 4) + 13;

    return randomVector(var_count);
}

// generates vector given specific number of variables
char* generateSpecificVector(int var_count) {
    return randomVector(var_count);
}

// generates vector
char* randomVector(int var_count) {
    int x;
    int vector_length = powl(2, var_count);

    char* gen_vector = (char*)malloc(vector_length*sizeof(char));
    for (int i = 0; i < vector_length; i++) {
        x = rand();

        if (x % 2 == 0) {
            gen_vector[i] = '0';
        }
        else {
            gen_vector[i] = '1';
        }
    }

    gen_vector[vector_length] = '\0';
    return gen_vector;
}


VERTEX* createVertex(char* data) {
    VERTEX* newVX = malloc(sizeof(VERTEX)); // allocation of correct space

    newVX->data = strdup(data); // data transfer
    newVX->index = 0;
    newVX->depth = 1;
    newVX->left = NULL; // pointer to left successor
    newVX->right = NULL; // pointer to right successor
    newVX->next = NULL; // pointer to next neighbor
    newVX->prev = NULL; // pointer to previous neighbor
    newVX->parent = NULL; // pointer to first parent

    return newVX;
}

// creates a non-reduced binary decision diagram according to given boolean function
BDD* BDD_create(BF* bfunkcia) {
    if ((is2Power(strlen(bfunkcia->vector)) == FALSE) || (checkVector(bfunkcia->vector)) == FALSE) { // conditions for correct input
        fprintf(stderr, "INPUT VECTOR WAS INCORRECT\n");
        exit(1);
    }
    else {
        printf("INPUT VECTOR WAS CORRECT\n");
    }

    BDD* bdd = (BDD*)malloc(sizeof(BDD));

    VERTEX* root = createVertex(bfunkcia->vector);
    bdd->root = root; // root assign


    int vector_length = strlen(root->data);

    int var_count = log2(vector_length); // computes number of variables from vector length using logarithm
    bdd->var_count = var_count;

    bdd->size = powl(2, var_count+1)-1; // number of vertices in non-reduced diagram is equal to this formula

    createDiagram(vector_length, root); // call to recursive function

    return bdd;
}

// updates depth for all vertices after reduction cycle
void updateDepth(VERTEX* currentVX) {
    if (currentVX->parent == NULL) {
        return;
    }
    else {
        currentVX->depth = currentVX->parent->depth;
        currentVX->depth++;
    }
}

// recursive creation of diagram
void createDiagram(int vector_length, VERTEX* root) {
    updateDepth(root); // depth update for current vertex

    if (vector_length >= 2) {
        vector_length /= 2;

        char* left_split = (char*)malloc(vector_length*sizeof(char));
        char* right_split = (char*)malloc(vector_length*sizeof(char));

        for (int i = 0; i < vector_length; i++) { // two following cycles split vector in the half
            left_split[i] = root->data[i];
        }
        left_split[vector_length]='\0';

        for (int i = 0; i < vector_length; i++) {
            right_split[i] = root->data[i + vector_length];
        }
        right_split[vector_length]='\0';

        VERTEX* left = createVertex(left_split);
        VERTEX* right = createVertex(right_split);

        left->index = getLeft(root->index); // index computation using binary heap-like formula
        right->index = getRight(root->index);

        if (vector_length != 1) { // parent pointer assignment
            left->parent = root;
            right->parent = root;
        }


        root->left = left;
        root->right = right;

        //updateHeight(root);

        createDiagram(vector_length, root->left); // recursive calls
        createDiagram(vector_length, root->right);

    }
}

/*
char BDD_use(BDD* bdd, char* vstupy) {
    int i = 0;
    VERTEX* currentVX = bdd->root;

    while (1) {
        if (vstupy[i] == '0') {
            currentVX = currentVX->left;
        }
        else if (vstupy[i] == '1') {
            currentVX = currentVX->right;
        }

        if (strlen(currentVX->data) == 1) {
            return *(currentVX->data);
        }
        i++;
    }
}
*/

// tests variable combination in the given bdd
char BDD_use(BDD* bdd, char* vstupy) {
    int i = 0;
    VERTEX* currentVX = bdd->root;

    while (1) {

        if (i != (currentVX->depth - 1)) { // if there is a jump in a reduced diagram
            i++;
            continue;
        }


        if (vstupy[i] == '0') { // if current variable is equal to zero, continue towards the left successor
            currentVX = currentVX->left;
        }
        else if (vstupy[i] == '1') {
            currentVX = currentVX->right;
        }


        if (strlen(currentVX->data) == 1) { // if leaf is found
            return *(currentVX->data);
        }

        i++;
    }
}


// updates indexing for all vertices except for leaves after the reduction
void updateIndexing(BDD* bdd, VERTEX* root) {
    if (root->next == NULL) { // if last non-leaf vertex is found
        bdd->last = root; // update last vertex
        return;
    }
    else {
        int index = root->index;
        index++;
        root->next->index = index; // increment new index and assign it accordingly
        updateIndexing(bdd, root->next); // recursion call
    }
}

// updates size for bdd after reduction is over
void updateSize(BDD* bdd, VERTEX* root) {
    updateIndexing(bdd, bdd->root); // update indexing
    bdd->size = 1;

    while (root->next != NULL) { // cycles through bdd horizontally
        bdd->size++;
        root = root->next;
    }

    bdd->size = bdd->size + 2; // manual leaf increment
}

// reduction signpost
int BDD_reduce(BDD* bdd) {
    /*
     * TODO 1. MERGE EQUIVALENT LEAFS, THUS LEAFS SHOULD BE ONLY 2 -> 0 and 1
     * TODO 2. MERGE ISOMORPHIC NODES
     * TODO 3. ELIMINATE REDUNDANT NODES
     */

    if(bdd == NULL) {
        return -1;
    }

    int initial_size = bdd->size;

    bdd = mergeEquivalentLeafs(bdd); // 1. - 1.st rule needs to be carried out only once

    for (int i = 0; i < bdd->var_count; i++) { // reduction rules must be done multiple times since rule 3 may create vertices that can be reduced by rule 2
        updateIndexing(bdd, bdd->root);
        mergeIsomorphic(bdd, i); // 2.
        eliminateRedundantNodes(bdd, bdd->root); // 3.
    }


    updateSize(bdd, bdd->root); // needed in some special cases where BDD size was calculated incorrectly

    initial_size = initial_size - bdd->size;

    return initial_size;
}

// creates horizontal connections in between vertices
void createConnections(BDD* bdd, VERTEX** vertexArray) {
    int index = (bdd->size)-3; // -3 because of leaves and inital index
    VERTEX* temp = vertexArray[index]; // assignment for the last non-leaf vertex
    bdd->last = temp; // update the value in bdd structure

    while (1) { // cycle that creates connections
        index--;
        temp->prev = vertexArray[index];

        temp = temp->prev;

        temp->next = vertexArray[index+1];
        if (index == 0) {
            return;
        }
    }

}

// traverses the non-reduced bdd and stores non-leaf vertices into an array with correct indexing from left to right
VERTEX** traverseTree(BDD* bdd, VERTEX* root, VERTEX** vertexArray) {
    if (root->right != NULL && root->left != NULL) {
        vertexArray[root->index] = root;

        traverseTree(bdd, root->left, vertexArray);
        traverseTree(bdd, root->right, vertexArray);
    }
    else {
        return vertexArray;
    }
}

// signpost for vertexArray creation
VERTEX** createVertexArray(BDD* bdd) {
    VERTEX** vertexArray = (VERTEX**)malloc(((bdd->size)-2)*sizeof(VERTEX*));

    vertexArray = traverseTree(bdd, bdd->root, vertexArray);

    return vertexArray;
}

// merges isomorphic nodes from bottom to root if two nodes have same data and identical children
void mergeIsomorphic(BDD* bdd, int cycle) {
    if (cycle == 0) {
        VERTEX** vertexArray = createVertexArray(bdd);

        createConnections(bdd, vertexArray);
    }

    // MERGE ITSELF
    VERTEX* comp_1 = bdd->last;
    VERTEX* comp_2 = comp_1->prev;
    VERTEX* comp_3;


    while (comp_1 != bdd->root) {

        if (comp_2 == NULL) { // TODO HIGHLY OPTIONAL
            return;
        }

        if ((strlen(comp_2->data)) != strlen(comp_1->data)) { // if length of data is not equal, next comparing vertex is selected
            comp_1 = comp_1->prev;
            comp_2 = comp_1->prev;
            if (comp_1 == bdd->root) { return; } // special case condition
        }


        if ((strcmp(comp_2->data, comp_1->data) == 0) &&
            (comp_1->left == comp_2->left) &&
            (comp_1->right == comp_2->right)) { // if the match is found



            comp_2->next->prev = comp_2->prev; // correct horizontal pointers
            comp_2->prev->next = comp_2->next;

            if (comp_2->parent->left == comp_2) { // correct parent pointers
                comp_2->parent->left = comp_1;
            }
            else if (comp_2->parent->right == comp_2) {
                comp_2->parent->right = comp_1;
            }

            bdd->size--;
        }


        if ((comp_2->left == comp_1) && comp_2 == bdd->root) { // condition if root is reached
            break;
        }


        comp_2 = comp_2->prev; // next compare
    }

}

/*
void mergeIsomorphicNodes(BDD* bdd, VERTEX* root) {
    int vector_length = strlen(root->data)/2;
    if (vector_length < 2) {
        return;
    }

    char* left_split = (char*)malloc(vector_length*sizeof(char));
    char* right_split = (char*)malloc(vector_length*sizeof(char));

    for (int i = 0; i < vector_length; i++) {
        left_split[i] = root->data[i];
    }
    left_split[vector_length]='\0';

    for (int i = 0; i < vector_length; i++) {
        right_split[i] = root->data[i + vector_length];
    }
    right_split[vector_length]='\0';

    if ((strcmp(left_split, right_split) != 0) &&
        (root->left->left != root->right->left) &&
        (root->right->right != root->left->right)) {

        mergeIsomorphicNodes(bdd, root->left);
        mergeIsomorphicNodes(bdd, root->right);
    }


    else if ((strcmp(left_split, right_split) == 0) &&
             (root->left->left == root->right->left) &&
             (root->right->right == root->left->right)) {

        root->right = root->left;
        bdd->size--;
    }

    return;
};*/


// 3rd rule - eliminates redundant nodes when both left and right successor point to the same vertex
void eliminateRedundantNodes(BDD* bdd, VERTEX* root) {
    if ((root->left == NULL) || (root->right == NULL)) { // when leaf is found
        return;
    }

    if ((root->left->left != NULL) && (root->left->right != NULL)) {
        if ((root->left->left) == (root->left->right)) { // when match is found on the left successor
            if (root->left->next == NULL) {
                root->left->prev->next = NULL;
            }
            else { // horizontal pointer fix
                root->left->next->prev = root->left->prev;
                root->left->prev->next = root->left->next;
            }

            root->left = root->left->left; // vertical pointer fix
            bdd->size--;

            if (strlen(root->left->data) != 1) { // updates parent pointer if its not a leaf
                root->left->parent = root;
            }

        }
    }

    if ((root->right->left != NULL) && (root->right->right != NULL)) {
        if ((root->right->left) == (root->right->right)) { // when match is found on the right successor
            if (root->right->next == NULL) {
                root->right->prev->next = NULL;
            }
            else { // horizontal pointer fix
                root->right->next->prev = root->right->prev;
                root->right->prev->next = root->right->next;
            }


            root->right = root->right->right; // vertical pointer fix
            bdd->size--;

            if (strlen(root->right->data) != 1) { // updates parent pointer if its not a leaf
                root->right->parent = root;
            }
        }
    }

    eliminateRedundantNodes(bdd, root->left); // recursive calls
    eliminateRedundantNodes(bdd, root->right);
}

// 1st rule - merges equivalent leafs into two leafs only
BDD* mergeEquivalentLeafs(BDD* bdd) {
    VERTEX* zero_vertex = createVertex("0");
    VERTEX* one_vertex = createVertex("1");

    bdd->zero_leaf = zero_vertex; // add the leafs into bdd structure
    bdd->one_leaf = one_vertex;

    bdd->zero_leaf->depth = bdd->var_count; // set correct depth for leafs
    bdd->zero_leaf->depth++;
    bdd->one_leaf->depth = bdd->zero_leaf->depth;

    merge(bdd, bdd->root); // merge all inside vertex that are just above the leafs

    bdd->size = bdd->size - powl(2, bdd->var_count) + 2; // update the size using constant formula

    return bdd;
}

// recursive merge to redirect all vertices into the two leafs
void merge(BDD* bdd, VERTEX* root) {

    if (strlen(root->data) != 2) { // when leaf is found

        merge(bdd, root->left); // recursive calls
        merge(bdd, root->right);

    }
    else { // correct redirecting on four possible cases
        if (root->data[0] == '0') {
            root->left = bdd->zero_leaf;
        }
        if (root->data[0] == '1') {
            root->left = bdd->one_leaf;
        }
        if (root->data[1] == '0') {
            root->right = bdd->zero_leaf;
        }
        if (root->data[1] == '1') {
            root->right = bdd->one_leaf;
        }
    }
}

/*
int main(void) {
    srand(time(0));
    BDD* bdd;
    char* str = "00010101"; // TODO [WARNING] STATIC INITIALIZATION
    BF* function = (BF*)malloc(sizeof(BF));
    function->vector = strdup(str);


    bdd = BDD_create(function);
    BDD_reduce(bdd);

    //printf("%s\n", bdd->root->right->right->data);

    printf("%c", BDD_use(bdd, "111"));

    //str = generateSpecificVector(3);

    free(function);
    free(bdd);

    return 0;
}*/