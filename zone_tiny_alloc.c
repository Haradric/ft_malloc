
#include <sys/mman.h>

#include "libft_malloc_zone.h"

zone_tiny_t *treg;

static void *init_region(void) {

    void *reg;

    reg = mmap(0, sizeof(zone_tiny_t), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (reg == NULL) {
        debug("can't allocate tiny region\n");
        return NULL;
    }
    debug("(%p) created tiny region\n", reg);
    return reg;
}

static size_t find_free_space(zone_tiny_t *reg, size_t size) {

    size_t i = 0;
    size_t j = size;

    while (i < TBLKNUM && j != 0) {
        if (reg->meta[i].first) {
            i += tb2b(reg->meta[i].bytes);
            j = size;
            continue ;
        }
        --j;
        ++i;
    }
    return (j == 0) ? i - size : -1;
}

static void *zone_tiny_alloc(zone_tiny_t *reg, size_t size) {

    size_t  i;

    i = find_free_space(reg, tb2b(size));
    if (i == (size_t)-1)
        return NULL;

    reg->meta[i].bytes = size;
    reg->meta[i].first = 1;
    reg->zones += 1;

    return reg->block[i];
}

void *tiny_alloc(size_t size) {

    zone_tiny_t *reg;
    void        *ret;

    if (!treg && !(treg = init_region()))
        return NULL;

    reg = treg;
    while (1) {
        if ((ret = zone_tiny_alloc(reg, size))) {
            debug("(%p) allocated %zu bytes\n", ret, size);
            return ret;
        }
        if (!reg->next)
            break ;
        reg = reg->next;
    }

    if ((reg->next = init_region()) && \
        (ret = zone_tiny_alloc(reg->next, size))) {
        debug("(%p) allocated %zu bytes\n", ret, size);
        return ret;
    }

    debug("can't allocate %zu bytes\n", size);
    return NULL;
}
