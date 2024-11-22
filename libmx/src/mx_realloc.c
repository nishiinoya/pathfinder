#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    if (ptr == NULL) {
        return malloc(size);
    }

    void *new_ptr = malloc(size);
    if (new_ptr == NULL) {
        return NULL;
    }

    size_t allocated_size = mx_malloc_usable_size(ptr);
    size_t size_to_copy;

    if (allocated_size > size) {
        size_to_copy = size;
    } else {
        size_to_copy = allocated_size;
    }

    mx_memcpy(new_ptr, ptr, size_to_copy);
    free(ptr);
    
    return new_ptr;
}
