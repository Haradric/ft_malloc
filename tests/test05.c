
#include <stdio.h>
#include <string.h>
#include "libft_malloc.h"

int main(void)
{
    char *addr;

    addr = malloc(16);
    free((void*)0);

    free((void *)addr + 5);

    if (realloc((void *)addr + 5, 10) == (void*)0)
	    printf("Bonjour\n");

    if (realloc((void *)addr + 5, 10) == (void*)0)
	    printf("Bonjour1\n");

    if (realloc((void *)addr, 20) == (void*)0)
	    printf("Bonjour2\n");

    if (realloc((void *)addr + 5, 10) == (void*)0)
	    printf("Bonjour3\n");
}
