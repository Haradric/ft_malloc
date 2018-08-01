
#include "libft_malloc_zone.h"

static int iter_tiny_regions(void *ptr) {

    zone_tiny_t *reg = treg;

    while (reg) {
        if (tiny_free(reg, ptr) == 0)
            return 0;
        reg = reg->next;
    }

    return -1;
}

static int iter_small_regions(void *ptr) {

    zone_small_t *reg = sreg;

    while (reg) {
        if (small_free(reg, ptr) == 0)
            return 0;
        reg = reg->next;
    }

    return -1;
}

static int iter_large_regions(void *ptr) {

    zone_large_t *reg = lreg;

    while (reg) {
        if (large_free(reg, ptr) == 0)
            return 0;
        reg = reg->next;
    }

    return -1;
}

int zone_free(void *ptr) {

    if (iter_tiny_regions(ptr) == 0)
        return 0;

    if (iter_small_regions(ptr) == 0)
        return 0;

    if (iter_large_regions(ptr) == 0)
        return 0;

    return -1;
}
