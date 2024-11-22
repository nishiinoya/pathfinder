#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    int s1_len = mx_strlen(s1);
    int s2_len = mx_strlen(s2);
    int i = s1_len;
    int j = 0;
    while (i < (s1_len + s2_len)) {
        s1[i] = s2[j];
        i++;
        j++;
    }
    s1[i++] = '\0';
    return s1;
}
