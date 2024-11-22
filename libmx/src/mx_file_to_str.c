#include "libmx.h"

static int open_file(const char *filename) {
    if (filename == NULL) {
        return -1;
    }
    return open(filename, O_RDONLY);
}

static int get_file_size(const char *filename) {
    int file_op = open_file(filename);
    if (file_op < 0) {
        return -1;
    }
    int len = 0;
    char buffer;
    while (read(file_op, &buffer, 1) > 0) {
        len++;
    }
    if (close(file_op) < 0) {
        return -1;
    }

    return len;
}

static char *read_file_content(const char *filename, int len) {
    int file_op = open_file(filename);
    if (file_op < 0) {
        return NULL;
    }

    char *file_str = mx_strnew(len); 
    if (file_str == NULL) {
        close(file_op);
        return NULL;
    }

    char buffer;
    for (int i = 0; read(file_op, &buffer, 1) > 0; i++) {
        file_str[i] = buffer;
    }

    if (close(file_op) < 0) {
        free(file_str);
        return NULL;
    }
    return file_str;
}

char *mx_file_to_str(const char *filename) {
    int file_size = get_file_size(filename);
    if (file_size < 0) {
        return NULL;
    }
 
    if (file_size == 0) {
        return mx_strnew(0);
    }

    return read_file_content(filename, file_size);
}
