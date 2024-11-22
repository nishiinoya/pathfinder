#include "libmx.h"

int mx_strlen(const char *s) {
    if (s == NULL) {
        return 0;
    }
    int i = 0; 
    int len = 0; 
    while (s[i] != '\0') {
        len++; 
        i++; 
    }
    return len; 
}
