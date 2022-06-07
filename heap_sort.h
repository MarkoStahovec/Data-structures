#define getParent(i) (((i)-1) / 2)
#define getLeft(i) (((i)*2) + 1)
#define getRight(i) (((i)*2) + 2)


void heapify(int numbers[], int quantity, int i) {
    int largest = i;
    int left = getLeft(i);
    int right = getRight(i);

    if ((left < quantity) && (numbers[left] > numbers[largest])) {
        largest = left;
    }

    if ((right < quantity) && (numbers[right] > numbers[largest])) {
        largest = right;
    }

    if (largest != i) {
        swap(&numbers[i], &numbers[largest]);

        heapify(numbers, quantity, largest);
    }
}


void heap_sort(int numbers[], int quantity) {

    for (int i = (quantity / 2) - 1; i >= 0 ; i--) {
        heapify(numbers, quantity, i);
    }

    for (int i = quantity-1; i > 0; i--) {
        swap(&numbers[0], &numbers[i]);

        heapify(numbers, i, 0);
    }

}


