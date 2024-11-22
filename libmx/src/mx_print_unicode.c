#include "libmx.h"

void mx_print_unicode(wchar_t c) {
    char byte[4];

    if (c < 0x80) {
        byte[0] = (char)c;
        write(1, byte, 1);
    } else if (c < 0x800) {
        byte[0] = (char)(0xC0 | (c >> 6));
        byte[1] = (char)(0x80 | (c & 0x3F));
        write(1, byte, 2);
    } else if (c < 0x10000) {
        byte[0] = (char)(0xE0 | (c >> 12));
        byte[1] = (char)(0x80 | ((c >> 6) & 0x3F));
        byte[2] = (char)(0x80 | (c & 0x3F));
        write(1, byte, 3);
    } else if (c < 0x110000) {
        byte[0] = (char)(0xF0 | (c >> 18));
        byte[1] = (char)(0x80 | ((c >> 12) & 0x3F));
        byte[2] = (char)(0x80 | ((c >> 6) & 0x3F));
        byte[3] = (char)(0x80 | (c & 0x3F));
        write(1, byte, 4);
    }
}

