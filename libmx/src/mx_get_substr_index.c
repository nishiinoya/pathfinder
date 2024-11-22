#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    if (str == NULL || sub == NULL) {
        return -2;
    }
    size_t sub_len = mx_strlen(sub);
    int i = 0;
    while (*str) {
        if (mx_strncmp(str, sub, sub_len) == 0) {
            return i;
        }
        i++;
        str++;
    }
    return -1;
}
