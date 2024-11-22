#include "libmx.h"

void mx_str_to_lower(char *str) {
    if (!str) return;

    for (int i = 0; str[i]; i++) {
        if (mx_isupper(str[i])) {
            str[i] = str[i] - 'A' + 'a';
        }
    }
}
