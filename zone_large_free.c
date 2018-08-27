
#include <sys/mman.h>
#include "libft_malloc_zone.h"

static void free_region(zone_large_t *reg) {

    zone_large_t *prev;

    if (reg == lreg) {
        lreg = reg->next;
    }
    else {
        prev = lreg;
        while (prev->next != reg)
            prev = prev->next;
        prev->next = reg->next;
    }

    munmap(reg->block, reg->meta.bytes);
    munmap(reg, sizeof(zone_large_t));
    debug("(%p) freed large region\n", reg);
}

int large_free(zone_large_t *reg, void *ptr) {

    // check if the pointer is located in the region
    if (ptr < (void *)reg->block || \
        ptr > ((void *)reg->block + reg->meta.bytes - 1))
        return FREE_ERR_WRONG_REG;

    // check whether the pointer is the begining of the block
    if (ptr != reg->block)
        return FREE_ERR_WRONG_ADDR;

    free_region(reg);

    debug("(%p) pointer was freed\n", ptr);
    return 0;
}
