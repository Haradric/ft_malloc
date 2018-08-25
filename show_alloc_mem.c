
#include <unistd.h>
#include "libft_malloc_zone.h"

static void _show_alloc_mem(int mode) {

    void    *reg;
    size_t  total = 0;

    reg = treg;
    while (reg) {
        show_reg_tiny(reg, &total, mode);
        reg = ((zone_tiny_t *)reg)->next;
    }

    reg = sreg;
    while (reg) {
        show_reg_small(reg, &total, mode);
        reg = ((zone_small_t *)reg)->next;
    }

    reg = lreg;
    while (reg) {
        show_reg_large(reg, &total, mode);
        reg = ((zone_large_t *)reg)->next;
    }

    print_str_size(STDOUT_FILENO, "Total: ", total, " bytes\n");
}

void show_alloc_mem(void) {

    _show_alloc_mem(0);
}

void show_alloc_mem_ex(void) {

    _show_alloc_mem(1);
}
