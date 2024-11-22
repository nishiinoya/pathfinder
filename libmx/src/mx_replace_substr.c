#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (!str || !sub || !replace)
        return NULL;

    int sub_len = mx_strlen(sub);
    int replace_len = mx_strlen(replace);
    int count = mx_count_substr(str, sub);
    if (count == 0)
        return mx_strdup(str);
    int new_len = mx_strlen(str) - count * sub_len + count * replace_len;

    char *result = mx_strnew(new_len);
    if (!result)
        return NULL;
    const char *current = str;
    char *res_ptr = result;
    const char *temp;

    while ((temp = mx_strstr(current, sub)) != NULL) {
        int chars_before = temp - current;
        mx_strncpy(res_ptr, current, chars_before);
        res_ptr += chars_before;
        mx_strcpy(res_ptr, replace);
        res_ptr += replace_len;
        current = temp + sub_len;
    }
    mx_strcpy(res_ptr, current);

    return result;
}
