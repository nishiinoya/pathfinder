#include "libmx.h"

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    if (fd < 0 || buf_size == 0 || lineptr == NULL)
        return -2;

    char *buffer = (char *)malloc(buf_size);
    if (buffer == NULL)
        return -2;

    char temp_char;
    size_t length = 0;
    int delimiter_hit = 0;
    ssize_t read_result;

    while ((read_result = read(fd, &temp_char, 1)) > 0) {
        if (temp_char == '\r')
            continue;

        if (temp_char == delim) {
            delimiter_hit = 1;
            break;
        }

        if (length >= buf_size - 1) {
            buf_size *= 2;
            char *resized_buffer = mx_realloc(buffer, buf_size);
            if (!resized_buffer) {
                free(buffer);
                return -2;
            }
            buffer = resized_buffer;
        }

        buffer[length++] = temp_char;
    }

    if (read_result == 0 && length == 0) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *lineptr = buffer;

    return delimiter_hit ? length : -1;
}
