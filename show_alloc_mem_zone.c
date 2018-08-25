
#include <unistd.h>
#include "libft_malloc_zone.h"

void show_reg_tiny(zone_tiny_t *reg, size_t *total, int mode) {

    size_t size;
    size_t i = 0;

    print_str_ptr(STDOUT_FILENO, "TINY : ", &reg->block[0], "\n");
    while (i < TBLKNUM) {
        if (reg->meta[i].first) {
            size = reg->meta[i].bytes;
            print_mem_dump(&reg->block[i], size, mode);
            *total += size;
            i += tb2b(size);
            continue ;
        }
        ++i;
    }
}

void show_reg_small(zone_small_t *reg, size_t *total, int mode) {

    size_t size;
    size_t i = 0;

    print_str_ptr(STDOUT_FILENO, "SMALL : ", &reg->block[0], "\n");
    while (i < SBLKNUM) {
        if (reg->meta[i].first) {
            size = reg->meta[i].bytes;
            print_mem_dump(&reg->block[i], size, mode);
            *total += size;
            i += sb2b(size);
            continue ;
        }
        ++i;
    }
}

void show_reg_large(zone_large_t *reg, size_t *total, int mode) {

    print_str_ptr(STDOUT_FILENO, "LARGE : ", &reg->block, "\n");
    print_mem_dump(reg->block, reg->meta.bytes, mode);

    *total += reg->meta.bytes;
}
