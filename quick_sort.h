
void median_of_three(int* numbers, int first, int last) {
    int middle = (first + last) / 2;

    if ((numbers[first] < numbers[middle] && numbers[middle] < numbers[last]) || (numbers[last] < numbers[middle] && numbers[middle] < numbers[first]))
        swap(&numbers[middle], &numbers[last]);

    else if ((numbers[middle] < numbers[first] && numbers[first] < numbers[last]) || (numbers[last] < numbers[first] && numbers[first] < numbers[middle]))
        swap(&numbers[first], &numbers[last]);

}


int part(int* numbers, int first, int last) {
    median_of_three(numbers, first, last);
    int pivot = numbers[last];
    int index = first;

    for (int i = first; i < last; i++) {
        if ((numbers[i] < pivot)) {
            swap(&numbers[i], &numbers[index]);
            index++;
        }
    }

    swap(&numbers[last], &numbers[index]);

    return index;
}


void quick_sort(int* numbers, int first, int last) {
    if (first >= last) return;

    int part_index = part(numbers, first, last);
    quick_sort(numbers, first, part_index-1);
    quick_sort(numbers, part_index+1, last);
}
