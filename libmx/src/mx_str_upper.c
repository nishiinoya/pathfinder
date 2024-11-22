#include "libmx.h"

void mx_str_to_upper(char *str) {
    if (!str) return;

    for (int i = 0; str[i]; i++) {
        if (mx_islower(str[i])) {
            str[i] = str[i] - 'a' + 'A'; 
        }
    }
}
