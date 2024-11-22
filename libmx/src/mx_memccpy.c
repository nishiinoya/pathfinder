#include "libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
    size_t i = 0;

    while (i < n) {
        ((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];

        if (((const unsigned char *)src)[i] == (unsigned char)c) {
            return (void *)&(((unsigned char *)dst)[i + 1]);
        }

        i++;
    }

    return NULL;
}
