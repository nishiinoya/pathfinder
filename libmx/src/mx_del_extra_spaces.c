#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
    if (str == NULL) return NULL; 
    char *trimmed_str = mx_strtrim(str);
    if (trimmed_str == NULL) return NULL; 

    char *result = (char *)malloc(mx_strlen(trimmed_str) + 1); 
    if (result == NULL) {
        free(trimmed_str);
        return NULL;
    }
    int j = 0;
    int inword_flag = 0;
    for (int i = 0; trimmed_str[i]; i++) {
        if (!mx_isspace(trimmed_str[i])) {
            result[j++] = trimmed_str[i]; 
            inword_flag = 1; 
        } else if (inword_flag) {
            result[j++] = ' '; 
            inword_flag = 0;
        }
    }
    result[j] = '\0';
    free(trimmed_str);

    return result;
}
