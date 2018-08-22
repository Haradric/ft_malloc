
#include "libft_malloc_zone.h"

static int is_fit(zone_tiny_t *reg, size_t index, size_t size) {

    size_t end = index + tb2b(size);
    size_t i = index + tb2b(reg->meta[index].bytes);

    while (i < end) {
        if (reg->meta[i].first == 1)
            return 0;
        ++i;
    }
    return 1;
}

static void *realloc(void *ptr, size_t old_size, size_t new_size) {

    void *new;

    new = zone_alloc(new_size);
    if (!new)
        return REALLOC_FAILURE;
    libft_memcpy(new, ptr, old_size);
    zone_free(ptr);

    return new;
}

void    *tiny_realloc(zone_tiny_t *reg, void *ptr, size_t size) {

    size_t block;

    // check if the pointer is located in the region
    if (ptr < (void *)&reg->block[0] && \
        ptr >= (void *)&reg->block[TBLKNUM] + sizeof(zone_tiny_t))
        return REALLOC_FAILURE;

    // check whether the pointer is the begining of the block
    block = (ptr - (void *)&reg->block[0]) / TBLKSZ;
    if (ptr != (void *)&reg->block[block])
        return REALLOC_FAILURE;

    if (reg->meta[block].first == 0)
        return REALLOC_FAILURE;

    if (is_fit(reg, block, size)) {
        // debug message
        reg->meta[block].bytes = size;
    }
    else {
        // debug message
        ptr = realloc(ptr, reg->meta[block].bytes, size);
    }

    return ptr;
}
