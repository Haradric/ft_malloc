
#include "libft_malloc_zone.h"

static void *iter_tiny_regions(void *ptr, size_t size) {

    zone_tiny_t *reg = treg;
    void        *ret;

    while (reg) {
        if ((ret = tiny_realloc(reg, ptr, size)))
            return ret;
        reg = reg->next;
    }

    return REALLOC_FAILURE;
}

static void *iter_small_regions(void *ptr, size_t size) {

    zone_small_t *reg = sreg;
    void         *ret;

    while (reg) {
        if ((ret = small_realloc(reg, ptr, size)))
            return ret;
        reg = reg->next;
    }

    return REALLOC_FAILURE;
}

static void *iter_large_regions(void *ptr, size_t size) {

    zone_large_t *reg = lreg;
    void         *ret;

    while (reg) {
        if ((ret = large_realloc(reg, ptr, size)))
            return ret;
        reg = reg->next;
    }

    return REALLOC_FAILURE;
}

void *zone_realloc(void *ptr, size_t size) {

    void *ret;

    if ((ret = iter_tiny_regions(ptr, size)))
        return ret;

    if ((ret = iter_small_regions(ptr, size)))
        return ret;

    if ((ret = iter_large_regions(ptr, size)))
        return ret;

    return REALLOC_FAILURE;
}
