#include <stdio.h>


int interpolationSearch(int arr[15], int lo, int hi, int x) {

    if ((lo <= hi) && (x <= arr[hi]) && (x >= arr[lo])) {
        int pos = lo + (((double)(hi - lo) / (arr[hi] - arr[lo])) * (x - arr[lo]));

        if (arr[pos] == x) {
            return pos;
        }

        if (x > arr[pos]) {
            return interpolationSearch(arr, pos + 1, hi, x);
        }

        if (x < arr[pos]) {
            return interpolationSearch(arr, lo, pos - 1, x);
        }
    }

    return -1;
}

int main()
{

    int arr[] = { 10, 12, 13, 16, 18, 19, 20, 21,
                  22, 23, 24, 33, 35, 42, 47 };
    int n = sizeof(arr) / sizeof(arr[0]);

    int x = 12;
    int index = interpolationSearch(arr, 0, n - 1, x);

    if (index != -1)
        printf("Element found at index %d", index);
    else
        printf("Element not found.");
    return 0;
}



