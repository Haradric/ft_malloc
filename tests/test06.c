
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "libft_malloc.h"

#define ZONES (1 << 16)
#define ZONE_SIZE 64

int main(void)
{
    unsigned char *z[ZONES] = {0};

    srand((unsigned int)time(NULL));
    for (size_t i = 0; i < ZONES; ++i) {
        z[i] = malloc(ZONE_SIZE);
        printf("malloc: %5zu = %p", i, z[i]);
        for (size_t j = 0; j < ZONE_SIZE; ++j) {
            z[i][j] = rand() % ('~' - '!') + '!';
        }
    }

    for (size_t i = 0; i < ZONES; ++i) {
        printf("free  : %5zu = %p", i, z[i]);
        free(z[i]);
    }
    show_alloc_mem();

    return 0;
}
