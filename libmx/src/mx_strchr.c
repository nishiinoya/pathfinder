#include "libmx.h"
char *mx_strchr(const char *s, int c) {
    while (*s != (char)c) {
        if (!*s)
            return (0);
        s++;
    }
    return ((char *)s);
}
