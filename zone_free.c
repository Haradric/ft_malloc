
#include <unistd.h>
#include "libft_malloc_zone.h"

static int iter_tiny_regions(void *ptr) {

    zone_tiny_t *reg = treg;
    int         ret;

    if (!reg)
        return FREE_ERR_WRONG_REG;

    while (reg) {
        ret = tiny_free(reg, ptr);
        if (ret == FREE_SUCCESS || ret == FREE_ERR_WRONG_ADDR)
            return ret;
        reg = reg->next;
    }

    return FREE_ERR_WRONG_ADDR;
}

static int iter_small_regions(void *ptr) {

    zone_small_t *reg = sreg;
    int          ret;

    if (!reg)
        return FREE_ERR_WRONG_REG;

    while (reg) {
        ret = small_free(reg, ptr);
        if (ret == FREE_SUCCESS || ret == FREE_ERR_WRONG_ADDR)
            return ret;
        reg = reg->next;
    }

    return FREE_ERR_WRONG_ADDR;
}

static int iter_large_regions(void *ptr) {

    zone_large_t *reg = lreg;
    int          ret;

    if (!reg)
        return FREE_ERR_WRONG_REG;

    while (reg) {
        ret = large_free(reg, ptr);
        if (ret == FREE_SUCCESS || ret == FREE_ERR_WRONG_ADDR)
            return ret;
        reg = reg->next;
    }

    return FREE_ERR_WRONG_ADDR;
}

int zone_free(void *ptr) {

    int ret;

    ret = iter_tiny_regions(ptr);
    if (ret == FREE_SUCCESS || ret == FREE_ERR_WRONG_ADDR)
        return ret;

    ret = iter_small_regions(ptr);
    if (ret == FREE_SUCCESS || ret == FREE_ERR_WRONG_ADDR)
        return ret;

    ret = iter_large_regions(ptr);
    if (ret == FREE_SUCCESS || ret == FREE_ERR_WRONG_ADDR)
        return ret;

    print_str_ptr(STDERR_FILENO, "malloc: *** error for object ", ptr, ": pointer being freed was not allocated\n");
    return FREE_ERR_WRONG_ADDR;
}
