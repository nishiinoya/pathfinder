#include "libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    if (!dst || !src || n == 0)
        return NULL;
    size_t i;
    i = 0;
    while (i < n) {
        ((char *)dst)[i] = ((char *)src)[i];
        i++;
    }
    return ((void *)dst);
}
