
#include <sys/mman.h>
#include "libft_malloc_zone.h"

void    *large_realloc(zone_large_t *reg, void *ptr, size_t size) {

    void *new;

    // check if the pointer is located in the region
    if (ptr < (void *)&reg->block && \
        ptr >= (void *)&reg->block + reg->meta.bytes)
        return REALLOC_FAILURE;

    // check whether the pointer is the begining of the block
    if (ptr != reg->block)
        return REALLOC_FAILURE;

    new = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (!new)
        return REALLOC_FAILURE;
    libft_memcpy(new, reg->block, (size < reg->meta.bytes) ? size : reg->meta.bytes);
    munmap(reg->block, reg->meta.bytes);
    debug("(%p) reallocated from %p (%zu bytes)\n", new, &reg->block, size);
    reg->block = new;
    reg->meta.bytes = size;

    return reg->block;
}
