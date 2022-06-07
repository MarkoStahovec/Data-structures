#include "dsa3.h"

// compare function for quick sort used later
int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

// generates all possible vector combinations -> needed to check correct return values from BDD_use
char** generateVariableCombinations(char** var_combinations, int var_count) {
    int num_of_combinations = powl(2, var_count);
    var_combinations = (char**)malloc(num_of_combinations*sizeof(char*));

    for (int i = 0; i < num_of_combinations; i++) {
        var_combinations[i] = (char*)malloc((var_count*sizeof(char)));

        int col_index = 0; // this variable ensures correct order of combinations in the array
        for (int j = var_count-1; j >= 0; j--) { // this cycle transforms integer number into a string binary value
            int binary = ((i >> j) & 1);
            var_combinations[i][col_index] = (binary == 1) ? '1' : '0';
            col_index++;
        }
        var_combinations[i][var_count] = '\0'; // manual terminator insertion at the end of the string
    }


    return var_combinations;
}


int tester(char** var_combinations, int var_count) {
    int correct = 0; // holds all correct BDD_use returns
    int reduced_VX_count = 0; // holds the amount of reduced vertices


    char* vector = generateSpecificVector(var_count);
    //char* vector = "1010110011100000";
    int vector_length = powl(2, var_count);

    BF* function = (BF*)malloc(sizeof(BF)); // the boolean function representation
    function->vector = strdup(vector);


    clock_t begin_create = clock(); // time when starting BDD creation

    BDD* bdd = BDD_create(function);

    clock_t end_create = clock();
    double result_create = (double)(end_create - begin_create) / CLOCKS_PER_SEC; // time calculation for BDD creation

    clock_t begin_reduction = clock(); // time when starting reduction

    reduced_VX_count = BDD_reduce(bdd);

    if (reduced_VX_count < 0) {
        fprintf(stderr, "BDD_reduce error.");
        exit(1);
    }

    clock_t end_reduction = clock();
    double result_reduction = (double)(end_reduction - begin_reduction) / CLOCKS_PER_SEC; // time calculation for reduction

    double reduction_percentage = ((double)reduced_VX_count / (reduced_VX_count + bdd->size)) * 100;

    printf("\nVECTOR LENGTH: %d\nVARIABLES: %d\n\n"
           "CURRENT NO. OF VERTICES: %d\nREDUCED VERTICES: %d\nREDUCTION PERCENTAGE: %.2lf%%\n"
           , vector_length, bdd->var_count, bdd->size, reduced_VX_count, reduction_percentage);

    clock_t begin_use = clock();

    for (int i = 0; i < vector_length; i++) { // this cycle checks correctness of a given vector to reduced BDD
        char result = BDD_use(bdd, var_combinations[i]);
        if (result < 0) {
            continue;
        }
        if (result == vector[i]) {
            correct++;
        }
    }

    clock_t end_use = clock();
    double result_use = (double)(end_use - begin_use) / CLOCKS_PER_SEC;


    printf("\nCORRECT: %d/%d\n\nBDD_CREATE TIME TAKEN: %.3lfs\nREDUCTION TIME TAKEN: %.3lfs",
           correct, vector_length, result_create, result_reduction);

    printf("\nUSE TIME TAKEN: %.3lfs\n\n***************************************\n***************************************\n", result_use);

    free(bdd);

    return reduced_VX_count;

}



int main(void) {
    srand(time(0)); // to ensure proper random generating

#define VAR_COUNT 15
    char** var_combinations = NULL;
    var_combinations = generateVariableCombinations(var_combinations, VAR_COUNT);
    //tester(var_combinations, VAR_COUNT);


#define CYCLE_COUNT 1

    clock_t begin_test = clock();

    int* reduced_VX_array = (int*)malloc(CYCLE_COUNT*sizeof(int));
    double reduced_all = 0;
    for (int i = 0; i < CYCLE_COUNT; i++) {
        reduced_VX_array[i] = tester(var_combinations, VAR_COUNT);
    }
    for (int i = 0; i < CYCLE_COUNT; i++) {
        reduced_all += reduced_VX_array[i];
    }
    reduced_all = reduced_all / CYCLE_COUNT;

    clock_t end_test = clock();

    double result = (double)(end_test - begin_test) / CLOCKS_PER_SEC;

    printf("\n*************************************************\n\n"
           "AVERAGE REDUCED VERTICES: %lf\nTIME TAKEN: %.3lfs\n", reduced_all, result);


    qsort(reduced_VX_array, CYCLE_COUNT, sizeof(int), cmpfunc);
    printf("\nMEDIAN OF REDUCED VERTICES: %d\n\n"
           "*************************************************", reduced_VX_array[CYCLE_COUNT/2]);


    return 0;
}
