#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    if (nbr == 0) {
        char *result = malloc(2);
        if (!result) return NULL;
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    char *result = malloc(16);
    if (!result) return NULL;

    int i = 0; 
    while (nbr != 0) {
        int rem = nbr % 16;
        char ch; 
        if (rem < 10) {
            ch = rem + '0'; 
        } else {
            ch = rem + 'a' - 10;
        }
        result[i] = ch; 
        i++; 
        nbr = nbr / 16;
    }
    result[i] = '\0';

    mx_str_reverse(result); 
    return result;
}
