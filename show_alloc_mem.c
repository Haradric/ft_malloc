
#include <unistd.h>

#include "libft_malloc_zone.h"

static void print_info(void *p1, void *p2, size_t size) {

    print_str_ptr(STDOUT_FILENO, "", p1, " - ");
    print_str_ptr(STDOUT_FILENO, "", p2, " : ");
    print_str_size(STDOUT_FILENO, "", size, " bytes\n");
}

static size_t show_reg_tiny(zone_tiny_t *reg) {

    size_t size;
    size_t i = 0;
    size_t total = 0;

    print_str_ptr(STDOUT_FILENO, "TINY : ", &reg->block[0], "\n");
    while (i < TBLKNUM) {
        if (reg->meta[i].first) {
            size = reg->meta[i].bytes;
            print_info(&reg->block[i], &reg->block[i] + size, size);
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

    print_str_ptr(STDOUT_FILENO, "SMALL : ", &reg->block[0], "\n");
    while (i < SBLKNUM) {
        if (reg->meta[i].first) {
            size = reg->meta[i].bytes;
            print_info(&reg->block[i], &reg->block[i] + size, size);
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

    print_str_ptr(STDOUT_FILENO, "LARGE : ", &reg->block, "\n");
    size = reg->meta.bytes;
    print_info(reg->block, reg->block + size, size);

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

    print_str_size(STDOUT_FILENO, "Total: ", total, " bytes\n");
}

