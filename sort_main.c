#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "insert_sort.h"
#include "selection_sort.h"
#include "bubble_sort.h"
#include "merge_sort.h"
#include "shell_sort.h"
#include "quick_sort.h"
#include "heap_sort.h"
#include "tree_sort.h"

#define QUANTITY 5
#define TRUE 1
#define FALSE 0

void print_array(int* numbers);
void tester(int* numbers, int quantity);

int main(void) {

    int numbers[QUANTITY] = {8, 2, 4, 3, 1};

    print_array(numbers);
    heap_sort(numbers, QUANTITY);
    print_array(numbers);


/*
    int* numbers = NULL;
    tester(numbers, QUANTITY);
*/

    return 0;
}


void print_array(int* numbers) {
    for (int i = 0; i < QUANTITY; i++) {
        printf("%d\t", numbers[i]);
    }
    printf("\n");
}


int* generateNumbers(int quantity) {
    int *arrayNumbers = (int *)malloc(quantity*sizeof(int)); // array for randomly generated keys

    for (int i = 0; i < quantity; i++) { // this cycle generates random numbers from 0 up to 10 000 000
        unsigned long x;
        x = rand();
        x <<= 15;
        x ^= rand();
        x %= 10000001;
        arrayNumbers[i] = x;
    }

    return arrayNumbers;
}


void tester(int* numbers, int quantity) {
    numbers = generateNumbers(quantity);
    int* unsorted = (int *)malloc(quantity*sizeof(int));
    for(int i = 0; i < quantity; i++) {
        unsorted[i] = numbers[i];
    }

    clock_t begin_ins = clock();

    insert_sort(numbers, quantity);

    clock_t end_ins = clock();
    double result_ins = (double)(end_ins - begin_ins) / CLOCKS_PER_SEC;

    for(int i = 0; i < quantity; i++) {
        numbers[i] = unsorted[i];
    }

    printf("1. insert completed.\n");

    clock_t begin_sel = clock();

    selection_sort(numbers, quantity);

    clock_t end_sel = clock();
    double result_sel = (double)(end_sel - begin_sel) / CLOCKS_PER_SEC;

    for(int i = 0; i < quantity; i++) {
        numbers[i] = unsorted[i];
    }

    printf("2. selection completed.\n");

    clock_t begin_bub = clock();

    bubble_sort(numbers, quantity);

    clock_t end_bub = clock();
    double result_bub = (double)(end_bub - begin_bub) / CLOCKS_PER_SEC;

    for(int i = 0; i < quantity; i++) {
        numbers[i] = unsorted[i];
    }

    printf("3. bubble completed.\n");

    clock_t begin_mer = clock();

    merge_sort(numbers, 0, quantity-1);

    clock_t end_mer = clock();
    double result_mer = (double)(end_mer - begin_mer) / CLOCKS_PER_SEC;

    for(int i = 0; i < quantity; i++) {
        numbers[i] = unsorted[i];
    }

    printf("4. merge completed.\n");

    clock_t begin_she = clock();

    shell_sort(numbers, quantity);

    clock_t end_she = clock();
    double result_she = (double)(end_she - begin_she) / CLOCKS_PER_SEC;

    for(int i = 0; i < quantity; i++) {
        numbers[i] = unsorted[i];
    }

    printf("5. shell completed.\n");

    clock_t begin_qui = clock();

    quick_sort(numbers, 0, quantity-1);

    clock_t end_qui = clock();
    double result_qui = (double)(end_qui - begin_qui) / CLOCKS_PER_SEC;

    for(int i = 0; i < quantity; i++) {
        numbers[i] = unsorted[i];
    }

    printf("6. quick completed.\n");

    clock_t begin_hea = clock();

    heap_sort(numbers, quantity);

    clock_t end_hea = clock();
    double result_hea = (double)(end_hea - begin_hea) / CLOCKS_PER_SEC;

    for(int i = 0; i < quantity; i++) {
        numbers[i] = unsorted[i];
    }

    printf("7. heap completed.\n");

    clock_t begin_tre = clock();

    tree_sort(numbers, quantity);

    clock_t end_tre = clock();
    double result_tre = (double)(end_tre - begin_tre) / CLOCKS_PER_SEC;

    for(int i = 0; i < quantity; i++) {
        numbers[i] = unsorted[i];
    }


    printf("Insertion sort on %d elements took %.3lfs\n"
           "Selection sort on %d elements took %.3lfs\n"
           "Bubble sort on %d elements took %.3lfs\n"
           "Merge sort on %d elements took %.3lfs\n"
           "Shell sort on %d elements took %.3lfs\n"
           "Quick sort on %d elements took %.3lfs\n"
           "Heap sort on %d elements took %.3lfs\n"
           "Tree sort on %d elements took %.3lfs\n",
           quantity, result_ins, quantity, result_sel, quantity, result_bub,
           quantity, result_mer, quantity, result_she, quantity, result_qui,
           quantity, result_hea, quantity, result_tre);
}





