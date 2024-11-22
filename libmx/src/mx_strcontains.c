#include "libmx.h"

bool mx_str_contains(const char *str, const char *sub) {
    if (!str || !sub) return false;

    while (*str) {
        const char *s1 = str;
        const char *s2 = sub;

        while (*s1 && *s2 && (*s1 == *s2)) {
            s1++;
            s2++;
        }
        if (!*s2) {
            return true;
        }
        str++;
    }
    return false; 
}

