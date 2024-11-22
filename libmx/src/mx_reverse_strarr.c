#include "libmx.h"

void mx_reverse_strarr(char** arr) {
    int len = 0;
    while (arr[len] != NULL) {
        len++;
    }
    for (int i = 0; i < len / 2; i++) {
        char* temp = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = temp;
    }
}
