#include "libmx.h"

void mx_printint(int num) {
    if (num == -2147483648) {
        write(1, "-2147483648", 11);
        return;
    }
    if (num < 0) {
        mx_printchar('-');
        num = -num;
    }

    if (num >= 10) {
        mx_printint(num / 10);
    }
    
    mx_printchar((num % 10) + '0');
}
