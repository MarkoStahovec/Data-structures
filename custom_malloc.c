#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "test_malloc.h"

/**
FIIT STU
Subject: Data structures and algorithms
Semester: SS 2020/2021
Author: Marko Stahovec

Assignment: 1
          : Custom implementation of malloc(); and its functionalities
***/

/*
 * This solution uses an implicit list with bidirectional coalescing, which makes the algorithm as fast as possible
 * with no unnecessary memory waste.
 */

void *heap_start = NULL;

/*
    Standard function to print out heap memory of a certain length in a byte format:
    0x9cf6e8:      00     00     00     00     00     00     00     00
 */
void printMemory(unsigned char *a, int array_length){
    int i;
    for(i = 0; i < array_length; i++){
        if (i % 8 == 0) {
            printf("\n0x%x: ", &(a[i]));
        }
        if (a[i] <= 15)
            printf("     0%X", a[i]);
        else {
            printf("  %5X", a[i]);
        }
    }
    printf("\n");
}

/*
    This function finds the first appropriate block in our heap and returns a pointer to it.
    If no such block is found, the function returns NULL and errorMessage.
 */
void *find_fit(unsigned int size) {
    unsigned int *header = (unsigned int*)(heap_start) + HEADER_SIZE/sizeof(unsigned int);   // we use this pointer to search for a suitable block in memory
    unsigned int *end_heap = ((unsigned int*)((unsigned char*)heap_start + (*(unsigned int*)heap_start)));   // this pointer holds an address of the last block of the memory

    // while cycle to search for a block
    while (header < end_heap) {
        if (!(IS_ODD(*header)) && *header >= size)
            return header;
        /*
         * If the block wasn't suitable, we add the number that's on the current address to the current address.
         * If the current block is allocated - thus the number on it is odd, the added number will be aligned in order to make a correct jump.
         */
        header = (header) + (((*header) & ~1L)/sizeof(unsigned int));
    }

    errorMessage(MEMORY_FULL);
    return NULL;
}


void *memory_alloc(unsigned int size)
{
    if(!heap_start) { // if no memory was initialized
        errorMessage(NO_INIT);
        return NULL;
    }

    if (size <= 0) { // if the given size is invalid
        errorMessage(INVALID_SIZE);
        return NULL;
    }


    unsigned int* header;
    unsigned int block_size = ALIGN(size + sizeof(unsigned int) + (FOOTER_SIZE));
    const unsigned int *end_heap = ((unsigned int*)((unsigned char*)heap_start + (*(unsigned int*)heap_start)));   // this pointer holds an address of the last block of the memory

    /*
     * In header we store the address of the block, that's eligible for allocation
     */
    header = find_fit(block_size);

    if (!header) { // ensuring condition
        errorMessage(MALLOC_ERROR);
        return NULL;
    }
    else {
        unsigned int old_size = *header; // variable that holds size of the block before the allocation to ensure correct split
        *header = block_size;
        unsigned int *footer = header + ((unsigned int)(block_size)/sizeof(unsigned int) - FOOTER_SIZE/sizeof(unsigned int));
        *footer = *header;



        // a few calculations for the new free block that was left after the split
        unsigned int *new_header = footer + HEADER_SIZE/sizeof(unsigned int);
        *new_header = old_size - block_size;
        unsigned int *new_footer = new_header + ((unsigned int)*new_header/sizeof(unsigned int) - FOOTER_SIZE/sizeof(unsigned int));
        if (new_footer > end_heap) {
            return NULL;
        }
        else {
            *new_footer = *new_header;
        }


        *header = *header | 1; // setting the last bit to be odd - to signalize that the block is allocated
        *footer = *footer | 1;

        return (char *)header + sizeof(unsigned int);
    }
}


/*
 * This function ensures proper coalescing when freeing a block, whomst predecessor/successor is not allocated
 * There are 4 cases possible:
 *          1. Freeing when previous and next blocks are both allocated
 *          2. Freeing when previous is not allocated, but the next one is
 *          3. Freeing when previous block is allocated, but the next one isn't
 *          4. Freeing when bot previous and next blocks are not allocated
 */
void *coalesce(unsigned int *current_block) {
    const unsigned int *end_heap = ((unsigned int*)((unsigned int*)heap_start + (*(unsigned int*)heap_start/sizeof(unsigned int))));  // this pointer holds an address of the last block of the memory


    unsigned int *next = (unsigned int *)((unsigned int *)current_block + ((*(unsigned char *)current_block) & ~1L)/sizeof(unsigned int)); // the two following variables hold the addresses of next and previous blocks
    unsigned int *prev = (unsigned int *)((unsigned int *)current_block - (*((unsigned char *)current_block-FOOTER_SIZE) & ~1L)/sizeof(unsigned int));


    unsigned short is_next_alloc; // these two variables may contain two values, 0 - block is not allocated, 1 = block is allocated;
    unsigned short is_prev_alloc;

    if (current_block == ((unsigned int *)heap_start + HEADER_SIZE/sizeof(unsigned int))) { // if the block is the first in our heap
        is_next_alloc = *next & 1;
        is_prev_alloc = 1;
        if (next >= end_heap) { // if its also the last
            is_next_alloc = 1;
        }
    }
    else if (next >= end_heap) { // if its the last block
        is_next_alloc = 1;
        is_prev_alloc = *next & 1;
    }
    else {
        is_next_alloc = *next & 1;
        is_prev_alloc = *prev & 1;
    }


    // Case 1
    if (is_prev_alloc == TRUE && is_next_alloc == TRUE) {
        *current_block = (*current_block) & ~1L;
        *(unsigned int *)((unsigned char *)current_block + (*(unsigned int *)current_block) - FOOTER_SIZE) = *current_block;
        memset(current_block + 1, 0, (unsigned char )(*(unsigned char *)current_block - FOOTER_SIZE - HEADER_SIZE));

        return current_block;
    }

        // Case 2
    else if (is_prev_alloc == FALSE && is_next_alloc == TRUE) {
        *prev = (*current_block + *prev) & ~1L; // new header
        //*(unsigned int *)((unsigned char *)prev + (*(unsigned int *)prev / sizeof(unsigned int) - FOOTER_SIZE) = *prev; // new footer
        *(unsigned int *)((unsigned char *)prev + (*(unsigned int *)prev) - FOOTER_SIZE) = *prev; // new footer
        memset(prev + 1, 0, (unsigned char )(*(unsigned char *)prev - FOOTER_SIZE - HEADER_SIZE));

        return prev;
    }

        // Case 3
    else if (is_prev_alloc == TRUE && is_next_alloc == FALSE) {
        *current_block = (*current_block + *next) & ~1L; // new header
        *(unsigned int *)((unsigned char *)current_block + (*(unsigned int *)current_block) - FOOTER_SIZE) = *current_block; // new footer
        memset(current_block + 1, 0, (unsigned char )(*(unsigned char *)current_block - FOOTER_SIZE - HEADER_SIZE));

        return current_block;
    }

        // Case 4
    else if (is_prev_alloc == FALSE && is_next_alloc == FALSE){
        *prev = (*prev + *current_block + *next) & ~1L; // new header
        *(unsigned int *)((unsigned char *)prev + (*(unsigned int *)prev) - FOOTER_SIZE) = *prev; // new footer
        memset(prev + 1, 0, (unsigned char )(*(unsigned char *)prev - FOOTER_SIZE - HEADER_SIZE));

        return prev;
    }

    return current_block;
}


int memory_free(void *valid_ptr)
{
    if (heap_start == NULL) {
        errorMessage(NO_INIT);
        return 1;
    }
    if ((memory_check(valid_ptr) == FALSE)) { // here is the call for the memory_check(); function
        errorMessage(INVALID_POINTER);
        return 1;
    }

    // when check returns 0, the program looks whether coalescing is possible
    coalesce((unsigned int*)(valid_ptr) - HEADER_SIZE/sizeof(unsigned int));

    return 0;
}

/*
 * Function that checks up, whether the given pointer to the freed block is valid
 */
int memory_check(void *ptr)
{
    //ptr = (unsigned int *)(ptr) - HEADER_SIZE/sizeof(unsigned int);  // proper type casting so we can do arithmetic operations

    if ((ptr == NULL) || (ptr < heap_start)) {
        return 0;
    }


    unsigned int *header = (unsigned int*)(heap_start) + HEADER_SIZE/sizeof(unsigned int);    // this pointer holds an address of the first allocatable block of the memory
    unsigned int *end_heap = ((unsigned int*)heap_start + (*(unsigned int*)heap_start/sizeof(unsigned int)));   // this pointer holds an address of the last block of the memory
    unsigned int block_size;

    if ((unsigned int *)ptr > end_heap || (unsigned int *)ptr < header) { // condition to check proper memory interval
        return 0;
    }

    while (header <= (unsigned int*)ptr) {
        block_size = *(unsigned int*)header;
        if (block_size & 1) { // if block is allocated
            if (header + 1 == ptr) { // check correction
                return 1;
            }
            block_size--; // to ensure correct jump
        }
        header = header + block_size/sizeof(unsigned int);
    }

    return 0;
}

/*
 * This function initializes the memory of given size into this form:
 * |-----------------------------------------------------------------------------------------------------------------
 * | FIXED 4BYTE HEADER -   |  1ST 4BYTE HEADER -      |                                      | 4BYTE FOOTER -      |
 * | no data can be stored  |  this is the header of   |                                      | this is the footer  |
 * | here                   |  the first block, where  | ***************memory*************** | of the whole memory |
 * |                        |  you can store the       |                                      | and the first block |
 * |                        |  information             |                                      |                     |
 * |-----------------------------------------------------------------------------------------------------------------
 */

void memory_init(void *ptr, unsigned int size)
{
    if (!ptr) { // checks for corrent arguments
        errorMessage(INVALID_POINTER);
        return;
    }
    if (size <= 0) {
        errorMessage(INVALID_SIZE);
        return;
    }

    memset(ptr, 0, size);
    heap_start = ptr; // here the function assigns the arguments to the global variable - addresswise and valuewise
    size = ALIGN_DOWN(size);
    *(unsigned int*)heap_start = size;

    // here the function creates first header and footer for the first giant available block
    unsigned int *first_block_header = (unsigned int*)(heap_start) + HEADER_SIZE/sizeof(unsigned int);
    *first_block_header = size - sizeof(unsigned int);

    unsigned int *first_block_footer = ((unsigned int*)heap_start + (size - FOOTER_SIZE)/sizeof(unsigned int));
    *first_block_footer = *first_block_header;

}

/*
 * Basic testing function that prints out the percentage evaluation of successful allocations.
 */
void memory_test(char *region, int minBlock, int maxBlock, int minMemory, int maxMemory, short randomBlockSize) {
    unsigned int successfulFrees = 0;
    unsigned int successfulAllocs = 0;
    unsigned int successfulBytes = 0;
    unsigned int totalAllocs = 0;
    unsigned int totalBytes = 0;
    unsigned int iterator = 0;
    double allocPercentage = 0;
    double bytePercentage = 0;
    char *pointer[99000];


    srand(time(0)); // this command randomizes the rand() values based on the current run-time
    unsigned int randomMemorySize = ((rand()) % (maxMemory - minMemory + 1)) + minMemory;
    unsigned int randomBlock = (rand() % (maxBlock - minBlock + 1) + minBlock);

    //printf("\n%d %d %d\n", randomNumber, randomMemorySize, randomBlock);

    //memset(region, 0, randomMemorySize);
    memory_init(region, randomMemorySize);



    while (totalBytes <= randomMemorySize) { // In this cycle, the blocks are being allocated based on the arguments until there is no memory left
        if (randomBlockSize == TRUE) {
            randomBlock = (rand() % (maxBlock - minBlock + 1) + minBlock);
        }

        // this condition ensures, that the percentage is always 100
        /*
        if (totalBytes + randomBlock > randomMemorySize) {
            break;
        }
         */

        pointer[iterator] = memory_alloc(randomBlock);
        totalBytes = totalBytes + randomBlock + HEADER_SIZE + FOOTER_SIZE;
        totalAllocs++;
        if (pointer[iterator]) { // if the mallocation was successful, we increment our particular values
            iterator++;
            successfulAllocs++;
            successfulBytes = successfulBytes + randomBlock + HEADER_SIZE + FOOTER_SIZE;
        }
        else {
            break;
        }
    }


    for (int j = iterator-1; j >= 0; j--) { // This cycle frees the allocated memory based on the previous mallocations using the iterator
        if (memory_check(pointer[j])) {
            memory_free(pointer[j]);
            successfulFrees++;
        }
        else {
            printf("\nWrong memory check.\n");
        }
    }


    allocPercentage = ((double)successfulAllocs / totalAllocs) * 100; // Percentage calculations using typecasting to prevent numerous error situations
    bytePercentage = ((double)successfulBytes / totalBytes) * 100;

    printf("\nMemory size of %d bytes: \nAllocated -> %.3f%% blocks (%.3f%% bytes).", randomMemorySize, allocPercentage, bytePercentage);
    printf("\nSuccessful frees: %d/%d\n-----------------------------------------------", successfulFrees, successfulAllocs);
}


int main(void)
{
/*
#define REGION_SIZE 104

    char region[REGION_SIZE];
    memset(region, 0, REGION_SIZE);
    memory_init(region, REGION_SIZE);
    printMemory(region,REGION_SIZE);


    char* pointer = (char*) memory_alloc(14);
    printMemory(region,REGION_SIZE);
    char* pointer_2 = (char*) memory_alloc(11);
    printMemory(region,REGION_SIZE);
    char* pointer_3 = (char*) memory_alloc(6);
    printMemory(region,REGION_SIZE);
    char* pointer_4 = (char*) memory_alloc(10);
    printMemory(region,REGION_SIZE);

    memory_free(pointer_2);
    printf("\nafter first free\n");
    printMemory(region,REGION_SIZE);

    memory_free(pointer_3);
    printf("\nafter second free\n");
    printMemory(region,REGION_SIZE);

    memory_free(pointer);
    printf("\nafter third free\n");
    printMemory(region,REGION_SIZE);

    memory_free(pointer_4);
    printf("\nafter last free\n");
    printMemory(region,REGION_SIZE);
*/

    char region[99000];
    memory_test(region, 8, 24, 50, 200, 0);
    memory_test(region, 8, 24, 50, 200, 1);
    memory_test(region, 8, 24, 65534, 65535, 1);
    memory_test(region, 1, 100000, 50000, 65536, 1);


    return 0;
}



