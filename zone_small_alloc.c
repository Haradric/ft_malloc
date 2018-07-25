
#include <sys/mman.h>

#include "libft_malloc_zone.h"

zone_small_t *sreg = NULL;

static void *init_region(void) {
    void *reg;

    reg = mmap(0, sizeof(zone_small_t), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (reg == NULL) {
        debug("can't allocate small region\n");
        return NULL;
    }
    debug("created small region (%p)\n", reg);
    return reg;
}

static size_t find_free_space(zone_small_t *reg, size_t size) {
    size_t i = 0;
    size_t j = size;

    while (i < SBLKNUM && j != 0) {
        if (reg->meta[i].first) {
            i += sb2b(reg->meta[i].bytes);
            j = size;
            continue ;
        }
        --j;
        ++i;
    }
    return (j == 0) ? i - size : -1;
}

static void *zone_small_alloc(zone_small_t *reg, size_t size) {

    size_t  blocks;
    size_t  i;

    blocks = sb2b(size);
    if ((i = find_free_space(reg, blocks)) == (size_t)-1) {
        debug("can't allocate %zu bytes(%zu blocks)\n", size, blocks);
        return NULL;
    }

    reg->meta[i].bytes = (uint32_t)size;
    reg->meta[i].first = 1;
    debug("allocated %zu bytes in %zu block(s) (block[%zu] -> %p)\n", \
          size, blocks, i, &reg->block[i]);
    return reg->block[i];
}

void *small_alloc(size_t size) {

    zone_small_t *reg;
    void        *ret;

    if (!sreg && !(sreg = init_region()))
        return NULL;

    reg = sreg;
    while (1) {
        if ((ret = zone_small_alloc(reg, size)))
            return ret;
        if (!reg->next)
            break ;
        reg = reg->next;
    }

    if ((reg->next = init_region()) && \
        (ret = zone_small_alloc(reg->next, size)))
        return ret;

    return NULL;
}
