#include "libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    if (src == NULL || dst == NULL)
        return NULL; 
    if (len < 0) {
        return NULL;
    }

    int i;
    for (i = 0; i < len; i++) {
        if (src[i] != '\0') {
            dst[i] = src[i];
        } else {
            break;
        }
    }
    
    for (; i < len; i++) {
        dst[i] = '\0';
    }

    return dst;
}
