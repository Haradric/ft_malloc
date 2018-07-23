
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include "libft_malloc.h"

void    *libft_malloc(size_t size) {
    void    *ptr;

    ptr = malloc_zone(size);
    if (!ptr) {
        errno = ENOMEM;
    }
    return ptr;
}
