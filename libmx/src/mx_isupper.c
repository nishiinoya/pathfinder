#include "libmx.h"

bool mx_isupper(int c) {
    if (c >= 65 && c <= 90) {
        return 1;
    } else {
        return 0;
    }
}
