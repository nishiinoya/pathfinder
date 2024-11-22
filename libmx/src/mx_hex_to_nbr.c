#include "libmx.h"

//converting hex to decimal 
unsigned long mx_hex_to_nbr(const char *hex) {
    if(hex == NULL) 
        return 0; 
    unsigned long result = 0;
    int i = 0;
    while (hex[i] != '\0') {
        char ch = hex[i];
        unsigned long val;
        if (ch >= '0' && ch <= '9') {
            val = ch - '0';
        } else if (ch >= 'A' && ch <= 'F') {
            val = ch - 'A' + 10;
        } else if (ch >= 'a' && ch <= 'f') {
            val = ch - 'a' + 10;
        } else {
            return 0;
        }
        result = (result << 4) | val; //shift left by 4 bits 
        i++;
    }
    return result;
}
