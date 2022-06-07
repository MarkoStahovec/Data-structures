#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0
#define DEF_LEAF_HEIGHT 1 // default leaf height
#define getMax(a, b) (((a) > (b)) ? (a) : (b)) // macro to compare two given values
#define getMin(a, b) (((a) < (b)) ? (a) : (b))


/**
FIIT STU
Subject: Data structures and algorithms
Semester: SS 2020/2021
Author: Marko Stahovec

Assignment: 2
          : Custom implementation of AVL binary tree and its functionalities
***/

// this structure represents one node/vertex in the binary tree
typedef struct node {
    uint32_t data;
    int32_t height;
    char* value;
    struct node* left;
    struct node* right;
} Node;

int32_t numofrotations = 0;

int32_t getHeight(Node* currentNode);
Node* getNewNode(uint32_t data, char* value);
Node* updateHeight(Node* currentNode);
char* searchNode(Node* currentNode, uint32_t key);
Node* checkRotation(Node* currentNode, uint32_t data);
Node* leftRotation(Node* predecessor);
Node* rightRotation(Node* predecessor);
Node* leftRightRotation(Node* currentNode);
Node* rightLeftRotation(Node* currentNode);
Node* findInsertion(Node *currentNode, uint32_t data, char* value);
Node* insertNode(Node* root, uint32_t data, char* value);
void printPreOrder(Node* currentNode);
void printInOrder(Node* currentNode);
void printPostOrder(Node* currentNode);

// returns current height of given node
int32_t getHeight(Node* currentNode) {
    if (currentNode == NULL) { // if current node doesnt yet exist, refer to its height as "0"
        return FALSE;
    }
    else {
        return currentNode->height;
    }
}

// update the height of given node comparing heights of its children and incrementing 1 to
// equalize the value to DEF_LEAF_HEIGHT
Node* updateHeight(Node* currentNode) {
    currentNode->height = getMax(getHeight(currentNode->left), getHeight(currentNode->right));
    currentNode->height++;

    return currentNode;
}

// returns new node when doing an insertion
Node* getNewNode(uint32_t data, char* value) {
    Node* newNode = malloc(sizeof(Node)); // allocation of correct space

    newNode->data = data; // assigning correct values
    newNode->height = DEF_LEAF_HEIGHT;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// this function rotates the structure of a tree like:
/*

     x                    y
      \                  / \
       y     ------->   x   z
        \
         z

 where x is predecessor, y is current and successor is z
 */
Node* leftRotation(Node* predecessor) {
    Node* current = predecessor->right;
    Node* successor = current->left;

    current->left = predecessor;
    predecessor->right = successor;

    updateHeight(predecessor); // to ensure correct cascade rotations, its mandatory to update heights asap
    updateHeight(current);
    //updateHeight(successor);
    numofrotations++;

    return current;
}

// this function rotates the structure of a tree like:
/*

       x                  y
      /                  / \
     y     ------->     z   x
    /
   z


 where x is predecessor, y is current and successor is z
 */
Node* rightRotation(Node* predecessor) {
    Node* current = predecessor->left;
    Node* successor = current->right;

    current->right = predecessor;
    predecessor->left = successor;

    updateHeight(predecessor); // to ensure correct cascade rotations, its mandatory to update heights asap
    updateHeight(current);
    //updateHeight(successor);
    numofrotations++;

    return current;
}

// this function rotates the structure of a tree like:
/*

       x                  x                  z
      /                  /                  / \
     y     ------->     z    ------->      y   x
      \                /
       z              y

 */
Node* leftRightRotation(Node* currentNode) {
    currentNode->left = leftRotation(currentNode->left);
    return rightRotation(currentNode);
}

// this function rotates the structure of a tree like:
/*

       x                  x                    z
        \                  \                  / \
         y     ------->     z    ------->    x   y
        /                    \
       z                      y

 */
Node* rightLeftRotation(Node* currentNode) {
    currentNode->right = rightRotation(currentNode->right);
    return leftRotation(currentNode);
}

// this function returns value that corresponds to given key in recursive manner
char* searchNode(Node* currentNode, uint32_t key) {
    if (currentNode == NULL) { // if the program tries to traverse further from the leaf
        return FALSE;
    }
    else if (key < currentNode->data) { // when key holds smaller value than actual node
        return searchNode(currentNode->left, key);
    }
    else if (key > currentNode->data) { // when key holds greater value than actual node
        return searchNode(currentNode->right, key);
    }
    else { // correct key found
        return currentNode->value;
    }
}

// this functions checks, whether its necessary to perform certain rotations
Node* checkRotation(Node* currentNode, uint32_t data) {
    int32_t currentBalance = getHeight(currentNode->left) - getHeight(currentNode->right);

    // if current balance holds greater value then |abs| > 2, then rotation is needed
    // there are 4 cases, which are displayed with its respective solution above in the code
    if ((currentBalance > 1) && (data < currentNode->left->data)) {
        return rightRotation(currentNode);
    }

    if ((currentBalance < -1) && (data >= currentNode->right->data)) {
        return leftRotation(currentNode);
    }

    if ((currentBalance > 1) && (data >= currentNode->left->data)) {
        currentNode = leftRightRotation(currentNode);
        return currentNode;
    }

    if ((currentBalance < -1) && (data < currentNode->right->data)) {
        currentNode = rightLeftRotation(currentNode);
        return currentNode;
    }

    return currentNode;
}

// this function looks up correct slot for the node in binary tree recursively
Node* findInsertion(Node *currentNode, uint32_t data, char* value) {
    if (currentNode == NULL) { // when leaf is found
        return getNewNode(data, value);
    }
    else if (data < currentNode->data) { // otherwise traverse accordingly
        currentNode->left = findInsertion(currentNode->left, data, value);
    }
    else if (data >= currentNode->data){
        currentNode->right = findInsertion(currentNode->right, data, value);
    }
    else {
        return currentNode;
    }

    updateHeight(currentNode);
    currentNode = checkRotation(currentNode, data); // call for checkRotation in case of imbalance

    return currentNode;
}

// this function inserts specific data and its value into the binary tree
Node* insertNode(Node* root, uint32_t data, char* value)  {

    Node* currentNode = findInsertion(root, data, value);

    //updateHeight(currentNode);

    return currentNode;
}

//a few tree print functions
void printPreOrder(Node* currentNode) {
    if (currentNode != NULL) {
        printf("data = %d, height = %d\n", currentNode->data, currentNode->height);
        printPreOrder(currentNode->left);
        printPreOrder(currentNode->right);
    }
    else {
        return;
    }
}

void printInOrder(Node* currentNode) {
    if (currentNode != NULL) {
        printInOrder(currentNode->left);
        printf("data = %d, height = %d\n", currentNode->data, currentNode->height);
        printInOrder(currentNode->right);
    }
    else {
        return;
    }
}

void printPostOrder(Node* currentNode) {
    if (currentNode != NULL) {
        printPostOrder(currentNode->left);
        printPostOrder(currentNode->right);
        printf("data = %d, height = %d\n", currentNode->data, currentNode->height);
    }
    else {
        return;
    }
}

