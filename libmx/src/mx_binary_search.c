#include "libmx.h"

static int compare_strings(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 < *str2) {
            return -1;
        } else if (*str1 > *str2) {
            return 1;
        }
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0') ? 0 : (*str1 == '\0' ? -1 : 1);
}

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int lowest = 0;
    int highest = size - 1;
    int comp = 0;

    while (lowest <= highest) {
        comp++;
        *count = comp;
        int mid = lowest + (highest - lowest) / 2;
        int cmp = compare_strings(s, arr[mid]);

        if (cmp == 0) {
            return mid;
        } else if (cmp > 0) {
            lowest = mid + 1;
        } else {
            highest = mid - 1;
        }
    }
    *count = 0;
    return -1;
}
