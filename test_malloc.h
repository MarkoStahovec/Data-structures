#define ALIGNMENT 4 // the formula for number alignment upwards, so the number is the divident of the number ALIGNMENT for correct block size allocation
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))
#define ALIGN_DOWN(size) (ALIGN(size+1)-4)
#define TRUE 1
#define FALSE 0

#define HEADER_SIZE 4
#define FOOTER_SIZE (HEADER_SIZE)

#define IS_ODD(x) ((x) & 1) // macro that checks, whether the given number is odd or even

// Clauses for different error situations
#ifndef ERRORS
#define ERRORS

#include <stdio.h>
typedef enum Errors
{
    NO_INIT = -1,
    MEMORY_FULL = -2,
    INVALID_SIZE = -3,
    MALLOC_ERROR = -4,
    INVALID_POINTER = -5,
    FREE_ERROR = -6
} Error;

void errorMessage(Error error) {
    switch (error) {
        case NO_INIT:
            fprintf(stderr,"\nMemory not initialized.");
            break;
        case MEMORY_FULL:
            fprintf(stderr, "\nMemory is full!");
            break;
        case INVALID_SIZE:
            fprintf(stderr, "\nInvalid size!");
            break;
        case MALLOC_ERROR:
            fprintf(stderr, "\nNo appropriate block found.");
            break;
        case INVALID_POINTER:
            fprintf(stderr, "\nInvalid pointer!");
            break;
        case FREE_ERROR:
            fprintf(stderr, "\nDeallocation error!");
            break;
        default:
            break;
    }
}

#endif

// function declarations
void printMemory(unsigned char *a,int array_length);
void *find_fit(unsigned int size);
void *memory_alloc(unsigned int size);
void *coalesce(unsigned int *freed_block);
int memory_free(void *valid_ptr);
int memory_check(void *ptr);
void memory_init(void *ptr, unsigned int size);
void memory_test(char *region, int minBlock, int maxBlock, int minMemory, int maxMemory, short randomBlockSize);

