#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} NODE;


NODE* createNode(int data) {
    NODE* node = (NODE*)malloc(sizeof(NODE));
    node->data = data;
    node->right = NULL;
    node->left = NULL;

    return node;
}


NODE* insert(NODE* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (root->data > data) {
        root->left = insert(root->left, data);
    }
    else if (root->data < data) {
        root->right = insert(root->right, data);
    }

    return root;
};


NODE* search(NODE* root, int data) {
    if (root == NULL) { return NULL; }
    else if (root->data > data) {
        return search(root->left, data);
    }
    else if (root->data < data) {
        return search(root->right, data);
    }
    else {
        return root;
    }
}


int secondLargest(NODE* root) {
    if (root == NULL) { return 0; }

    if (!root->right && root->left && root->left->right) {
        return root->left->right->data;
    }

    while (root) {
        if ((root->left) && (!root->right)) {
            return root->left->data;
        }

        if ((root->right) && !(root->right->left) && !(root->right->right)) {
            return root->data;
        }

        root = root->right;
    }
}


bool checkTree(NODE* node, int min, int max) {
    if (!node) { return true; }

    if (node->data < min || node->data > max) {
        return false;
    }

    return checkTree(node->left, min, node->data) && checkTree(node->right, node->data, max);
}


void check(NODE* root) {
    if (checkTree(root, INT_MIN, INT_MAX)) {
        printf("Valid tree.");
    }
    else {
        printf("Invalid tree.");
    }
}


void rec_closest(NODE* root, int key, int *closest) {
    if (root == NULL) { return; }
    if (key == root->data) {
        *closest = root->data;
        return;
    }

    if (abs(*closest - key) > abs(root->data - key)) {
        *closest = root->data;
    }

    if (root->data > key) {
        rec_closest(root->left, key, closest);
    }
    else {
        rec_closest(root->right, key, closest);
    }
}


int closest(NODE* root, int key) {
    int* closest = &(root->data);

    rec_closest(root, key, closest);

    return *closest;
}


int main(void) {
    NODE* root = NULL;



    root = insert(root, 9);
    root = insert(root, 17);
    root = insert(root, 22);
    root = insert(root, 20);
    root = insert(root, 4);
    root = insert(root, 3);
    root = insert(root, 6);
    root = insert(root, 5);
    root = insert(root, 7);


/*
    root = insert(root, 15);
    root->left = createNode(12);
    root->left->left = createNode(10);
    root->left->right = createNode(8);
*/

/*
    root = insert(root, 15);
    root->right = createNode(20);
    root->right->right = createNode(24);
    root->right->left = createNode(18);
    root->right->left->left = createNode(16);
    root->right->left->right = createNode(17);
*/
    check(root);
    printf("\nSECOND LARGEST ELEMENT: %d", secondLargest(root));
    printf("\nCLOSEST ELEMENT: %d", closest(root, 12));

    return 0;
}

