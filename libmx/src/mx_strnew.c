#include "libmx.h"

char *mx_strnew(const int size) {
    if (size < 0)
        return NULL;
    char *new = NULL;
    new = (char *)malloc((size + 1) * sizeof(char));
    int i = 0;
    while (i < size) {
        new[i] = '\0';
        i++;
    }
    new[i] = '\0';
    return new;
}
