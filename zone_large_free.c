
#include <sys/mman.h>

#include "libft_malloc_zone.h"

static void remove_from_list(zone_large_t *reg) {

    zone_large_t *prev;

    if (reg == lreg) {
        lreg = reg->next;
        return ;
    }

    prev = lreg;
    while (prev->next != reg)
        prev = prev->next;

    prev->next = reg->next;
}

int large_free(zone_large_t *reg, void *ptr) {

    if (ptr != reg->block)
        return -1;

    remove_from_list(reg);
    munmap(reg->block, reg->meta.bytes);
    munmap(reg, sizeof(zone_large_t));

    debug("pointer was freed (%p)\n", ptr);
    return 0;
}
