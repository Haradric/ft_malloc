
#include <sys/mman.h>

#include "libft_malloc_zone.h"

static void *init_region(void) {
    void *reg;

    reg = mmap(0, sizeof(zone_large_t), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (reg == NULL) {
        debug("can't allocate large region\n");
        return NULL;
    }
    debug("(%p) created large region\n", reg);
    return reg;
}

void *large_alloc(size_t size) {

    zone_large_t *reg;
    zone_large_t *last;

    if (!(reg = init_region()))
        return NULL;

    if (!(reg->block = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0))) {
        munmap(reg, sizeof(zone_large_t));
        debug("can't allocate %zu bytes\n", size);
        return NULL;
    }

    reg->meta.bytes = size;
    last = lreg;
    if (last) {
        while (last->next)
            last = last->next;
        last->next = reg;
    } else {
        lreg = reg;
    }

    debug("(%p) allocated %zu bytes\n", reg->block, size);
    return reg->block;
}
