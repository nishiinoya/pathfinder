#include "libmx.h"

int mx_sqrt(int x) {
    if (x < 0) return 0;
    if (x == 0) return 0;
    if (x == 1) return 1;

    int low = 1;
    int high = x;
    int mid;

    while (low <= high) {
        mid = low + (high - low) / 2;

        if (mid == x / mid) {
            return mid;
        } else if (mid > x / mid) {
            high = mid - 1;
        } else {
            low = mid + 1; 
        }
    }

    return 0; 
}
