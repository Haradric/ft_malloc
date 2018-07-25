
#include "libft_malloc.h"
#include "libft_malloc_zone.h"

void    *malloc_zone(size_t size) {

    if (!size)
        return NULL;

    if (size <= TZONEMAXSZ) {
        debug("using tiny region\n");
        return (tiny_alloc(size));
    }
    else if (size <= SZONEMAXSZ) {
        debug("using small region\n");
        return (zone_small_alloc(size));
    }
    else {
        debug("using large region\n");
        return (zone_large_alloc(size));
    }
}
