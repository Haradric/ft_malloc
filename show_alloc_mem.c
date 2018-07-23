
#include <stdio.h>

#include "libft_malloc_zone.h"

void show_alloc_mem(void) {

    size_t total = 0;

    total += show_alloc_mem_tiny();
    //total += show_alloc_mem_small();
    //total += show_alloc_mem_large();

    printf("Total: %zu bytes\n", total);
}

