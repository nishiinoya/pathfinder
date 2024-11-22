#include "libmx.h"

static int mx_partition(char **arr, int left, int right, int *swaps) {
    int pivot_i = left + (right - left) / 2; 
    int pivot_len = mx_strlen(arr[pivot_i]);
    int i = left;
    int j = right;

    while (i <= j) {
        while (mx_strlen(arr[i]) < pivot_len || 
               (mx_strlen(arr[i]) == pivot_len && mx_strcmp(arr[i], arr[pivot_i]) < 0)) {
            i++;
        }
        while (mx_strlen(arr[j]) > pivot_len || 
               (mx_strlen(arr[j]) == pivot_len && mx_strcmp(arr[j], arr[pivot_i]) > 0)) {
            j--;
        }
        if (i <= j) {
            if (i != j) {
                mx_swapstr(&arr[i], &arr[j]);
                (*swaps)++;
            }
            i++;
            j--;
        }
    }
    return i; 
}

int mx_quicksort(char **arr, int left, int right) {
    if (arr == NULL || left >= right) {
        return 0;
    }

    int swaps = 0;
    int pivot_index = mx_partition(arr, left, right, &swaps);

    swaps += mx_quicksort(arr, left, pivot_index - 1);
    swaps += mx_quicksort(arr, pivot_index, right);

    return swaps;
}
