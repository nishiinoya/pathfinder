#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
    unsigned char *big_ptr = (unsigned char *)big;
    unsigned char *little_ptr = (unsigned char *)little;

    if (little_len == 0 || little_len > big_len) {
        return NULL;
    }

    for (size_t i = 0; i <= big_len - little_len; i++) {
        if (mx_memcmp(big_ptr + i, little_ptr, little_len) == 0) {
            return big_ptr + i;
        }
    }

    return NULL;
}
