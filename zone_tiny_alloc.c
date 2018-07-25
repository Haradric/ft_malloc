
#include <sys/mman.h>

#include "libft_malloc_zone.h"

zone_tiny_t *treg = NULL;

static int init_region(void) {
    treg = mmap(0, sizeof(zone_tiny_t), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (treg == NULL) {
        debug("can't allocate memory for tiny region\n");
        return 0;
    }
    return 1;
}

static size_t find_free_space(size_t size) {
    size_t i = 0;
    size_t j = size;

    while (i < TBLKNUM && j != 0) {
        if (tmeta[i].first) {
            i += tb2b(tmeta[i].bytes);
            j = size;
            continue ;
        }
        --j;
        ++i;
    }
    return (j == 0) ? i - size : -1;
}

void *zone_tiny_alloc(size_t size) {

    size_t  blocks;
    size_t  i;

    if ((treg == NULL && !init_region()) || !size)
        return NULL;

    blocks = tb2b(size);
    if ((i = find_free_space(blocks)) == (size_t)-1) {
        debug("can't allocate %zu bytes(%zu blocks)\n", size, blocks);
        return NULL;
    }

    tmeta[i].bytes = size;
    tmeta[i].first = 1;
    debug("allocated %zu bytes(%zu blocks) starting from %zu block\n", size, blocks, i);
    return tblock[i];
}


