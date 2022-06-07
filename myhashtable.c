#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>


#define TRUE 1
#define FALSE 0
#define THRESHOLD_FACTOR 0.75 // constant that determines resizing threshold
#define BASE_TABLE_SIZE 500

/**
FIIT STU
Subject: Data structures and algorithms
Semester: SS 2020/2021
Author: Marko Stahovec

Assignment: 2
          : Custom implementation of hash table and its functionalities
***/

// this structure represents one item in the hashtable
typedef struct item {
    uint32_t key;
    char* value;
} ITEM;

// this structure holds array of items and a few hashtable parameters
typedef struct table {
    int32_t collisions;
    int32_t size;
    int32_t count;
    ITEM** items;
} TABLE;


ITEM* getNewItem(uint32_t key, char* value);
TABLE* getNewTable();
uint32_t getHash(uint32_t key, int32_t tableSize);
char* searchTable(TABLE* table, uint32_t key);
TABLE* insertTable(TABLE* table, uint32_t key, char* value);
int32_t getSize(int32_t minimum);
TABLE* resizeCheck(TABLE* table);
TABLE* resize(TABLE* oldTable);


// this function creates an item with given parameters
ITEM* getNewItem(uint32_t key, char* value) {
    ITEM* newItem = malloc(sizeof(ITEM));

    newItem->key = key;
    newItem->value = strdup(value); // strdup to ensure correct string transfer

    return newItem;
}

// this function creates a hashtable with given parameters
TABLE* getNewTable(int32_t newSize) {
    TABLE* table = malloc(sizeof(TABLE));

    table->collisions = 0;
    table->size = newSize;
    table->count = 0;
    table->items = calloc((size_t)table->size, sizeof(ITEM*));

    return table;
}

// create a pseudo-random hashcode for given key
uint32_t getHash(uint32_t key, int32_t tableSize) {
    unsigned long int code = 0;

    // do several rounds of multiplication with prime constants
    code = (code * 17 + (0x7FCA27 * key));

    // make sure value is within table's bounds
    code = code % tableSize;

    return code;
}

// basic function that searches through table for given key
char* searchTable(TABLE* table, uint32_t key) {
    int32_t index = getHash(key, table->size); // get hash for given key
    ITEM* item = table->items[index];

    while(item != NULL) { // cycle through hashtable until NULL is met (ensures that incorrect keys dont loop forever)
        if(item->key == key) {
            return item->value;
        }
        if ((index + 1) == (table->size)) { // when array hits the last slot, we loop from the beginning
            index = 0;
            item = table->items[index];
        }

        else { // try next item
            item = table->items[index+1];
            index++;
        }
    }

    return NULL;
}

// this functions inserts a specific item into an array of items on an index, thats determined by the hash function
TABLE* insertTable(TABLE* table, uint32_t key, char* value) {
    int32_t index = getHash(key, table->size);

    if (key) {
        ITEM* newItem = getNewItem(key, value);
        if (table->items[index] == NULL) { // when program finds index in O(1) time
            table->items[index] = newItem;
        }
        else { // else program loops through allocated items until we hit NULL index in an array
            table->collisions++;
            while (table->items[index] != NULL) {
                if ((table->items[index]->key) == (key)) { // if same key is found, the value gets updated
                    table->items[index]->value = value;
                    return table;
                }
                if (index + 1 == (table->size)) { // when program hits end of an array
                    index = 0;
                }
                else {
                    index++;
                }
            }

            table->items[index] = newItem;
        }

        table->count++;
        table = resizeCheck(table); // check if the hashtable exceeded the threshold value
    }

    return table;
}

// returns a pseudo random number roughly twice as big as given
int32_t getSize(int32_t minimum) {
    int32_t number = minimum * 2;
    while ((number % 2 == 0) || (number % 3 == 0) || (number % 5 == 0) || (number % 7 == 0)) {
        number = number - 1;
    }

    return number;
}

// checks if threshold factor is exceeded
TABLE* resizeCheck(TABLE* table) {
    float tableCount = (float) table->count;
    float tableSize = (float) table->size;
    float usedPercentage = tableCount/tableSize;
    if (usedPercentage > THRESHOLD_FACTOR) {
        table = resize(table);
    }

    return table;
}

// resizes table to double its old size
TABLE* resize(TABLE* oldTable) {
    int32_t newSize = getSize(oldTable->size);
    TABLE* newTable = getNewTable(newSize);
    newTable->collisions = 0;
    //printf("\n%d\n", newTable->collisions);

    // rehash every item
    for (int i = 0; i < oldTable->size; i++) { // cycle through old array and rehash all items
        ITEM* item = oldTable->items[i];

        if (item != NULL) {
            insertTable(newTable, item->key, item->value);
        }
    }

    //free(oldTable);

    return newTable;
}


int main(void) {
    TABLE* table = getNewTable(BASE_TABLE_SIZE);
    table->collisions = 0;
    table = insertTable(table, 105250262, "Smrdi");
    table = insertTable(table, 211318592, "Nesmrdi");
    table = insertTable(table, 211318592, "Haha");
    table = insertTable(table, 124252422, "lolo");
    table = insertTable(table, 985251312, "Strbo");
    table = insertTable(table, 952523251, "Szarka");
    table = insertTable(table, 281523036, "Skurla");
    table = insertTable(table, 825202625, "Szacsko");
    table = insertTable(table, 172648654, "Smorada");

    printf("\n%s\n", searchTable(table, 825202625));
    printf("%d", table->collisions);

    return 0;
}