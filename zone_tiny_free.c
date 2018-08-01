
#include "libft_malloc_zone.h"

int tiny_free(zone_tiny_t *reg, void *ptr) {

    size_t block;

    if (ptr < (void *)&reg->block[0] && \
        ptr > (void *)&reg->block[TBLKNUM])
        return -1;

    block = (ptr - (void *)&reg->block[0]) / sizeof(zone_tiny_t);
    if (ptr != (void *)&reg->block[block])
        return -1;

    reg->meta[block].first = 0;
    reg->meta[block].bytes = 0;

    debug("pointer was freed (%p)\n", ptr);
    return 0;
}
