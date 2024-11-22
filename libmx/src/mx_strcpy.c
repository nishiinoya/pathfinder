#include "libmx.h"

char *mx_strcpy(char *dst, const char *src) {
    if (src == NULL || dst == NULL)
        return NULL;
    int i;
    for (i = 0; src[i] != '\0'; i++) {
        dst[i] = src[i];
    }
    dst[i] = '\0';
    return dst;
}
