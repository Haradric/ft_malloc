
#include "libft_malloc_zone.h"

static int is_fit(zone_small_t *reg, size_t index, size_t size) {

    size_t end = index + sb2b(size);
    size_t i = index + sb2b(reg->meta[index].bytes);

    if (end > SBLKNUM)
        return 0;

    while (i < end) {
        if (reg->meta[i].first == 1)
            return 0;
        ++i;
    }
    return 1;
}

static void *realloc(void *ptr, size_t old_size, size_t new_size) {

    void *new;

    debug("(%p) trying to realloc\n",ptr);
    new = zone_alloc(new_size);
    if (!new)
        return REALLOC_FAILURE;
    libft_memcpy(new, ptr, old_size);
    zone_free(ptr);

    return new;
}

void    *small_realloc(zone_small_t *reg, void *ptr, size_t size) {

    size_t block;

    // check if the pointer is located in the region
    if (ptr < (void *)&reg->block[0] || \
        ptr > ((void *)&reg->block[SBLKNUM] - 1))
        return REALLOC_FAILURE;

    // check whether the pointer is the begining of the block
    block = (ptr - (void *)&reg->block[0]) / SBLKSZ;
    if (ptr != (void *)&reg->block[block])
        return REALLOC_FAILURE;

    if (reg->meta[block].first == 0)
        return REALLOC_FAILURE;

    if (is_fit(reg, block, size)) {
        reg->meta[block].bytes = (uint32_t)size;
        debug("(%p) changed size to %zu\n", &reg->block[block], size);
    }
    else {
        ptr = realloc(ptr, reg->meta[block].bytes, size);
    }

    return ptr;
}
