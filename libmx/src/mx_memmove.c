#include "libmx.h"

void mx_memmove(void *dest, const void *src, size_t len) {
    unsigned char *ptr_dest;
    const unsigned char *ptr_src;
    size_t i;

    ptr_dest = (unsigned char *)dest;
    ptr_src = (const unsigned char *)src;
    i = 0;

    if (ptr_dest > ptr_src) {
        while (len--)
            ptr_dest[len] = ptr_src[len];
    } else {
        while (i < len) {
            ptr_dest[i] = ptr_src[i];
            i++;
        }
    }
}
