
#include <sys/mman.h>
#include "libft_malloc_zone.h"

static void free_region(zone_small_t *reg) {

    zone_small_t *prev;

    if (reg == sreg && reg->next == NULL)
        return ;

    if (reg == sreg && reg->next != NULL) {
        sreg = reg->next;
    }
    else {
        prev = sreg;
        while (prev->next != reg)
            prev = prev->next;
        prev->next = reg->next;
        munmap(reg, sizeof(zone_small_t));
        debug("(%p) freed small region\n", reg);
    }
}

int small_free(zone_small_t *reg, void *ptr) {

    size_t block;

    // check if the pointer is located in the region
    if (ptr < (void *)&reg->block[0] || \
        ptr > ((void *)&reg->block[SBLKNUM] - 1))
        return FREE_ERR_WRONG_REG;

    // check whether the pointer is the begining of the block
    block = (ptr - (void *)&reg->block[0]) / SBLKSZ;
    if (ptr != (void *)&reg->block[block])
        return FREE_ERR_WRONG_ADDR;

    // check if the block has been allocated
    if (reg->meta[block].first == 0)
        return FREE_ERR_WRONG_ADDR;

    reg->meta[block].first = 0;
    reg->meta[block].bytes = 0;
    reg->zones -= 1;

    if (!reg->zones)
        free_region(reg);

    debug("(%p) pointer was freed\n", ptr);
    return 0;
}
