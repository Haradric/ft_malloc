
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include "libft_malloc_zone.h"

void    *libft_malloc(size_t size) {

    void    *ptr;

    ptr = malloc_zone(size);
    if (!ptr) {
        errno = ENOMEM;
    }
    return ptr;
}

void    free(void *ptr) {

    if (zone_free(ptr) == -1)
        printf("malloc: *** error for object %p: pointer being freed was not allocated\n", ptr);
}
