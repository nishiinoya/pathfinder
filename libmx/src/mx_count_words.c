#include "libmx.h"

int mx_count_words(const char *str, char c) {
    if (str == NULL) {
        return -1;
    }

    int inword_flag = 0; 
    int counter = 0; 

    while (*str) {
        if (*str == c) {
            inword_flag = 0;
        } else if (inword_flag == 0) {
            inword_flag = 1; 
            counter++; 
        }
        str++;
    }

    return counter;
}
