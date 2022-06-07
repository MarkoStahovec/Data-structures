#define TRUE 1
#define FALSE 0


void bubble_sort(int* numbers, int quantity) {
    char swapped;
    do {
        swapped = FALSE;
        for (int i = 0; i < quantity-1; i++) {
            if (numbers[i] > numbers[i+1]) {
                swap(&numbers[i], &numbers[i+1]);
                swapped = TRUE;
            }
        }
    } while (swapped);
}
