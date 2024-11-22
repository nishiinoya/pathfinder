#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return (char *)haystack;
    }
    size_t n = mx_strlen(needle);
    while (*haystack) {
        if (mx_memcmp(haystack, needle, n) == 0) {
            return (char *)haystack;
        }
        haystack++;
    }
    return NULL;
}
