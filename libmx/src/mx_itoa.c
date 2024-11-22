#include "libmx.h"

static int mx_len_num(int n) {
    int len = (n <= 0) ? 1 : 0; 
    if (n == 0) return 1;
    while (n != 0) {
        len++;
        n /= 10;
    }
    return len;
}

char *mx_itoa(int number) {
    int len = mx_len_num(number);
    char *str = malloc((len + 1) * sizeof(char)); 
    if (str == NULL) return NULL;
    
    str[len] = '\0';

    if (number == -2147483648) {
        str[0] = '-';
        str[1] = '2';
        number = 147483648;  
    } else if (number < 0) {
        str[0] = '-';    
        number = -number; 
    } else if (number == 0) {
        str[0] = '0';      
        return str; 
    }

    for (int i = len - 1; number > 0; i--) {
        str[i] = (number % 10) + '0'; 
        number /= 10;
    }

    return str;
}
