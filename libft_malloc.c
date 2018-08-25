
#include <stdint.h>
#include <errno.h>
#include "libft_malloc_zone.h"

void    *zone[3] = {0};

void    *malloc(size_t size) {

    void    *ptr;

    ptr = zone_alloc(size);
    if (!ptr)
        errno = ENOMEM;

    return ptr;
}

void    free(void *ptr) {

    zone_free(ptr);
}

void    *realloc(void *ptr, size_t size) {

    void *new;

    new = zone_realloc(ptr, size);
    if (new == NULL)
        errno = ENOMEM;

    return new;
}
