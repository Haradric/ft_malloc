
#include <stddef.h>
#include "libft_malloc_zone.h"

void    *zone_alloc(size_t size) {

    if (!size)
        return NULL;

    if (size <= TZONEMAXSZ) {
        debug("using tiny region\n");
        return (tiny_alloc(size));
    }
    else if (size <= SZONEMAXSZ) {
        debug("using small region\n");
        return (small_alloc(size));
    }
    else if (size <= LZONEMAXSZ) {
        debug("using large region\n");
        return (large_alloc(size));
    }
    debug("sorry, but not today\n");
    return NULL;
}
