#include "libmx.h"

char *mx_strjoin(const char *s1, const char *s2) {
    if (s1 == NULL && s2 == NULL) {
        return NULL;
    }
    if (s1 == NULL) {
        return mx_strdup(s2);
    }
    if (s2 == NULL) {
        return mx_strdup(s1);
    }

    char *str;
    int len1 = mx_strlen(s1);
    int len2 = mx_strlen(s2);

    str = malloc(sizeof(char) * (len1 + len2 + 1));
    if (!str) {
        return NULL;
    }

    for (int i = 0; i < len1; i++) {
        str[i] = s1[i];
    }
    for (int i = 0; i < len2; i++) {
        str[len1 + i] = s2[i];
    }
    str[len1 + len2] = '\0';
    return str;
}
