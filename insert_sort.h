
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void insert_sort(int numbers[], int quantity) {
    int i, key, j;
    for (i = 1; i < quantity; i++) {
        key = numbers[i];
        j = i - 1;

        while (j >= 0 && numbers[j] > key) {
            numbers[j + 1] = numbers[j];
            j = j - 1;
        }
        numbers[j + 1] = key;
    }
}