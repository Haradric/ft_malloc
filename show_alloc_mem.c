
#include <stdio.h>

#include "libft_malloc_zone.h"

static size_t show_reg_tiny(zone_tiny_t *reg) {

    size_t size;
    size_t i = 0;
    size_t total = 0;

    printf("TINY : %p\n", &reg->block[0]);
    while (i < TBLKNUM) {
        if (reg->meta[i].first) {
            size = reg->meta[i].bytes;
            printf("%p - %p : %zu bytes\n", &reg->block[i], &reg->block[i] + size, size);
            total += size;
            i += tb2b(size);
            continue ;
        }
        ++i;
    }
    return total;
}

static size_t show_reg_small(zone_small_t *reg) {

    size_t size;
    size_t i = 0;
    size_t total = 0;

    printf("SMALL : %p\n", &reg->block[0]);
    while (i < SBLKNUM) {
        if (reg->meta[i].first) {
            size = reg->meta[i].bytes;
            printf("%p - %p : %zu bytes\n", &reg->block[i], &reg->block[i] + size, size);
            total += size;
            i += sb2b(size);
            continue ;
        }
        ++i;
    }
    return total;
}

static size_t show_reg_large(zone_large_t *reg) {

    size_t size;

    printf("LARGE : %p\n", reg->block);
    size = reg->meta.bytes;
    printf("%p - %p : %zu bytes\n", reg->block, reg->block + size, size);

    return size;
}

void show_alloc_mem(void) {

    zone_tiny_t  *tiny;
    zone_small_t *small;
    zone_large_t *large;
    size_t       total = 0;

    tiny = treg;
    while (tiny) {
        total += show_reg_tiny(tiny);
        tiny = tiny->next;
    }

    small = sreg;
    while (small) {
        total += show_reg_small(small);
        small = small->next;
    }

    large = lreg;
    while (large) {
        total += show_reg_large(large);
        large = large->next;
    }

    printf("Total: %zu bytes\n", total);
}

