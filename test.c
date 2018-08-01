
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft_malloc.h"

#define INPUT_SIZE 256

int main(void) {
    char    input[INPUT_SIZE + 1] = {0};
    void    *ptr;
    size_t  size;

    sleep(1);
    while (read(0, input, INPUT_SIZE)) {
        size = atoi(input);
        printf("size = %zu\n", size);
        ptr = malloc(size);
        show_alloc_mem();
        (void)ptr;
    }

    return (0);
}
