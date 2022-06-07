#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "bst_avl.h"
#include "taken_rbtree.h"
#include "myhashtable.h"
#include "other_hash.h"

#define MAX_LINE_LENGTH 20


void readFile(char* buff, FILE* file) { // upgraded fgets for file reading
    fgets(buff, MAX_LINE_LENGTH, file); // line load
    size_t len = strlen(buff);
    if(len <= 1) {
        //printf("Incorrect input\n");
    }
    else {
        if(buff[len - 2] == '\r' || buff[len - 2] == '\n') {
            buff[len - 2] = '\0'; // manual terminator addition
        }
        if(buff[len - 1] == '\r' || buff[len - 1] == '\n') {
            buff[len - 1] = '\0'; // manual terminator addition
        }
    }
}



char** loadNames(char** name_array, FILE* file) { // function to load names from txt file
    int i = 0;
    file = fopen("names.txt", "r");

    if(!file){
        printf("cant open file\n");
        exit(1);
    }
    name_array = (char**)malloc(sizeof(char *)*10000);
    for (i = 0; i < 10000; i++) {
        name_array[i] = (char *)malloc(MAX_LINE_LENGTH * sizeof(int));
        fgets(name_array[i], 200, file);
        printf("%s", name_array[i]);
    }

/*
    for (i=0; i<3; i++)
    {
        fgets(name_array[i], 200, file);
        printf("%s", name_array[i]);
    }
*/
    return name_array;
}


void myBinaryTreeTester(int32_t noOfElements, short searchAll, int32_t *arrayNumbers) {
    Node* rootNode = NULL; // initial root

    clock_t begin_insertion = clock(); // time when starting insertion

    for (int i = 0; i < noOfElements; i++) { // insertion of all elements
        rootNode = insertNode(rootNode, arrayNumbers[i], "test");
    }


    clock_t end_insertion = clock();
    double result_time_insert = (double)(end_insertion - begin_insertion) / CLOCKS_PER_SEC; // time calculation for insertion
    printf("%d elements inserted in %.3lf seconds\n", noOfElements, result_time_insert);

    if (searchAll == TRUE) {
        clock_t begin_all_search = clock(); // time when starting search
        for (int i = 0; i < noOfElements; i++) { // search cycle
            searchNode(rootNode, arrayNumbers[i]);
        }
        clock_t end_all_search = clock();
        double result_time_search = (double)(end_all_search - begin_all_search) / CLOCKS_PER_SEC; // time calculation for search
        printf("%d elements found in %.3lf seconds\n", noOfElements, result_time_search);
    }

}

void stolenBinaryTreeTester(int32_t noOfElements, short searchAll, int32_t *arrayNumbers) {
    struct cell* root = NULL;

    clock_t begin_insertion = clock(); // time when starting insertion

    for (int i = 0; i < noOfElements; i++) { // insertion of all elements
        rb_insert(&root, arrayNumbers[i], "test");
    }


    clock_t end_insertion = clock();
    double result_time_insert = (double)(end_insertion - begin_insertion) / CLOCKS_PER_SEC; // time calculation for insertion
    printf("%d elements inserted in %.3lf seconds\n", noOfElements, result_time_insert);

    if (searchAll == TRUE) {
        clock_t begin_all_search = clock(); // time when starting search
        for (int i = 0; i < noOfElements; i++) { // search cycle
            searchRB(root, arrayNumbers[i]);
        }
        clock_t end_all_search = clock();
        double result_time_search = (double)(end_all_search - begin_all_search) / CLOCKS_PER_SEC; // time calculation for search
        printf("%d elements found in %.3lf seconds\n", noOfElements, result_time_search);
    }

}


void myHashTableTester(int32_t noOfElements, short searchAll, int32_t *arrayNumbers) {
    TABLE* table = getNewTable(BASE_TABLE_SIZE);
/*
    FILE* file = NULL;
    char **names = NULL;
    names = loadNames(names, file);
*/

    //table->collisions = 0;

    clock_t begin_insertion = clock(); // time when starting insertion

    for (int i = 0; i < noOfElements; i++) { // insertion of all elements
        table = insertTable(table, arrayNumbers[i], "test");
    }


    clock_t end_insertion = clock();
    double result_time_insert = (double)(end_insertion - begin_insertion) / CLOCKS_PER_SEC; // time calculation for insertion
    printf("%d elements inserted in %.3lf seconds\n", noOfElements, result_time_insert);

    if (searchAll == TRUE) {
        clock_t begin_all_search = clock(); // time when starting search
        for (int i = 0; i < noOfElements-1; i++) { // search cycle
            searchTable(table, arrayNumbers[i]);
        }
        clock_t end_all_search = clock();
        double result_time_search = (double)(end_all_search - begin_all_search) / CLOCKS_PER_SEC; // time calculation for search
        printf("%d elements found in %.3lf seconds\n", noOfElements, result_time_search);
    }

}

void chainHashTableTester(int32_t noOfElements, short searchAll, int32_t *arrayNumbers) {
    ht_t* htable = ht_create();

    /*
    FILE* file = NULL;
    char **names = NULL;
    names = loadNames(names, file);
     */


    clock_t begin_insertion = clock(); // time when starting insertion

    for (int i = 0; i < noOfElements; i++) { // insertion of all elements
        ht_set(htable, arrayNumbers[i], "test");
    }


    clock_t end_insertion = clock();
    double result_time_insert = (double)(end_insertion - begin_insertion) / CLOCKS_PER_SEC; // time calculation for insertion
    printf("%d elements inserted in %.3lf seconds\n", noOfElements, result_time_insert);

    if (searchAll == TRUE) {
        clock_t begin_all_search = clock(); // time when starting search
        for (int i = 0; i < noOfElements-1; i++) { // search cycle
            //printf("%d\n", table->items[i]->key);
            ht_get(htable, arrayNumbers[i]);
        }
        clock_t end_all_search = clock();
        double result_time_search = (double)(end_all_search - begin_all_search) / CLOCKS_PER_SEC; // time calculation for search
        printf("%d elements found in %.3lf seconds\n", noOfElements, result_time_search);
    }

}


int main(void) {
    srand(time(0)); // to ensure random numbers for each run

#define NO_OF_ELEMENTS 2000000 // constant for how many elements will be inserted and searched

    int32_t *arrayNumbers = (int32_t *)malloc(NO_OF_ELEMENTS*sizeof(int32_t)); // array for randomly generated keys

    for (int i = 0; i < NO_OF_ELEMENTS; i++) { // this cycle generates random numbers from 0 up to 10 000 000
        unsigned long x;
        x = rand();
        x <<= 15;
        x ^= rand();
        x %= 10000001;
        arrayNumbers[i] = x;
        //printf("%d\n", arrayNumbers[i]);
    }



    printf("***** ***** AVL BINARY TREE ***** *****\n");
    myBinaryTreeTester(NO_OF_ELEMENTS, 1, arrayNumbers); // my implentation for binary tree
    //printf("%d\n", numofrotations);

    printf("\n***** ***** R&B BINARY TREE ***** *****\n");
    stolenBinaryTreeTester(NO_OF_ELEMENTS, 1, arrayNumbers); // internet implentation for binary tree
    //printf("%d\n", rbrotations);

    printf("\n***** ***** LINEAR PROBING HASHTABLE ***** *****\n");
    myHashTableTester(NO_OF_ELEMENTS, 1, arrayNumbers); // my implentation for hash table

    printf("\n***** ***** CHAINING HASHTABLE ***** *****\n");
    chainHashTableTester(NO_OF_ELEMENTS, 1, arrayNumbers); // internet implentation for binary tree

    return 0;
}

