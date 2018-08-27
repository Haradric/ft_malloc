
#include <sys/mman.h>
#include "libft_malloc_zone.h"

static void free_region(zone_tiny_t *reg) {

    zone_tiny_t *prev;

    if (reg == treg && reg->next == NULL)
        return ;

    if (reg == treg && reg->next != NULL) {
        treg = reg->next;
    }
    else {
        prev = treg;
        while (prev->next != reg)
            prev = prev->next;
        prev->next = reg->next;
        munmap(reg, sizeof(zone_tiny_t));
        debug("(%p) freed tiny region\n", reg);
    }
}

int tiny_free(zone_tiny_t *reg, void *ptr) {

    size_t block;

    // check if the pointer is located in the region
    if (ptr < (void *)&reg->block[0] || \
        ptr > ((void *)&reg->block[TBLKNUM] - 1))
        return FREE_ERR_WRONG_REG;

    // check whether the pointer is the begining of the block
    block = (ptr - (void *)&reg->block[0]) / TBLKSZ;
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
