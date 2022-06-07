#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEF_TABLE_SIZE 5

typedef struct item {
    char* data;
    struct item* left;
    struct item* right;
} ITEM;


typedef struct table {
    int size;
    ITEM** items;
} TABLE;


ITEM* rec_insert(ITEM* root, char* data);
ITEM* rec_search(ITEM* root, char* data);


TABLE* initTable() {
    TABLE* table = (TABLE*)malloc(sizeof(TABLE));
    table->size = DEF_TABLE_SIZE;
    table->items = (ITEM**)calloc(DEF_TABLE_SIZE, sizeof(ITEM*));

    return table;
}


ITEM* createItem(char* data) {
    ITEM* item = (ITEM*)malloc(sizeof(ITEM));
    item->data = strdup(data);
    item->left = NULL;
    item->right = NULL;

    return item;
}


int hash(char* data, int table_size) {
    int i, len = strlen(data), h = 0;
    for (i = 0; i < len; i++) {
        h = 31*h + data[i];
        h %= table_size;
    }

    return h;
}


TABLE* insert(TABLE* table, char* data) {
    int index = hash(data, table->size);
    table->items[index] = rec_insert(table->items[index], data);

    return table;
}


ITEM* rec_insert(ITEM* root, char* data) {
    if (root == NULL) {
        return createItem(data);
    }
    if (strcmp(root->data, data) > 0) {
        root->left = rec_insert(root->left, data);
    }
    else if (strcmp(root->data, data) < 0) {
        root->right = rec_insert(root->right, data);
    }

    return root;
}


bool search(TABLE* table, char* data) {
    int index = hash(data, table->size); // get hash for given key
    ITEM* item = rec_search(table->items[index], data);

    if (item) { return true; }

    return false;
}

ITEM* rec_search(ITEM* root, char* data) {
    if (root == NULL) { return NULL; }
    else if (strcmp(root->data, data) > 0) {
        return rec_search(root->left, data);
    }
    else if (strcmp(root->data, data) < 0) {
        return rec_search(root->right, data);
    }
    else {
        return root;
    }
}


int main(void) {
    TABLE* table = initTable();
    table = insert(table, "Marko");
    table = insert(table, "Lukas");
    table = insert(table, "Adrian");
    table = insert(table, "Richard");

    printf("%d", search(table, "Marek"));

    return 0;
}



