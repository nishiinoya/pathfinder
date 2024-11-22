#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    const unsigned char *byte_ptr = (const unsigned char *)s;
    unsigned char target_char = (unsigned char)c;

    while (n > 0) {
        if (byte_ptr[n - 1] == target_char) {
            return (void *)(byte_ptr + n - 1);
        }
        n--;
    }
    
    return NULL;
}
