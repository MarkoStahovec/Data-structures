
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} NODE;


NODE* getNewNode(int data) {
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


NODE* insert(NODE* root, int data) {
    if (root == NULL) root = getNewNode(data);

    else if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}


void inorder(NODE* root, int* numbers, int* i){
    if(root != NULL){
        inorder(root->left, numbers, i);
        numbers[(*i)++] = root->data;
        inorder(root->right, numbers, i);
    }
}


void tree_sort(int* numbers, int quantity) {
    NODE* root = NULL;

    for (int i = 0; i < quantity; i++) {
        root = insert(root, numbers[i]);
    }

    int i = 0;
    inorder(root, numbers, &i);
}


