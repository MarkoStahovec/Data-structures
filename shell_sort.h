

void shell_sort(int* numbers, int quantity) {
    int idx;
    for (int i = quantity/2; i > 0; i /= 2) {
        for (int j = 0; j < quantity; j++) {
            int temp = numbers[j];

            idx = j;
            while ((idx >= i) && (numbers[idx - i] > temp)) {
                numbers[idx] = numbers[idx - i];

                idx -= i;
            }

            numbers[idx] = temp;
        }
    }
}