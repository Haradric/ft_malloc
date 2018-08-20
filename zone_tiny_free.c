
#include "libft_malloc_zone.h"

int tiny_free(zone_tiny_t *reg, void *ptr) {

    size_t block;

    // check if the pointer is located in the region
    if (ptr < (void *)&reg->block[0] && \
        ptr >= (void *)&reg->block[TBLKNUM] + sizeof(zone_tiny_t))
        return FREE_ERR_WRONG_REG;

    // check whether the pointer is the begining of the block
    block = (ptr - (void *)&reg->block[0]) / sizeof(zone_tiny_t);
    if (ptr != (void *)&reg->block[block])
        return FREE_ERR_WRONG_ADDR;

    // check if the block has been allocated
    if (reg->meta[block].first == 0)
        return FREE_ERR_WRONG_ADDR;

    reg->meta[block].first = 0;
    reg->meta[block].bytes = 0;

    debug("pointer was freed (%p)\n", ptr);
    return 0;
}
