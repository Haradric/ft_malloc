
#include <stdio.h>

#include "libft_malloc_zone.h"

size_t show_alloc_mem_tiny(void) {

    size_t size;
    void   *first;
    void   *last;
    size_t i = 0;
    size_t total = 0;

    printf("TINY : %p\n", treg);
    while (i < TBLKNUM) {
        if (tmeta[i].first) {
            size = tmeta[i].bytes;
            first = &tblock[i];
            last = first + size;
            printf("%p - %p : %zu bytes\n", first, last, size);
            total += size;
            i += tb2b(size);
            continue ;
        }
        ++i;
    }
    return total;
}

void show_alloc_mem(void) {

    size_t total = 0;

    total += show_alloc_mem_tiny();
    //total += show_alloc_mem_small();
    //total += show_alloc_mem_large();

    printf("Total: %zu bytes\n", total);
}

