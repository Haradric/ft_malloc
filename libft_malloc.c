
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
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

    if (zone_free(ptr) == FREE_ERR_WRONG_ADDR)
        print_str_ptr(STDERR_FILENO, "malloc: *** error for object ", ptr, ": pointer being freed was not allocated\n");
}

void    *realloc(void *ptr, size_t size) {

    void *new;

    new = zone_realloc(ptr, size);
    if (new == NULL)
        errno = ENOMEM;

    return new;
}
