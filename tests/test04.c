
#include <stdio.h>
#include <string.h>
#include "libft_malloc.h"

#define M (1024 * 1024)

int main(void)
{
	char *addr1;
	char *addr2;
	char *addr3;

	addr1 = (char*)malloc(16*M);
	strcpy(addr1, "Bonjour\n");
	addr2 = (char*)malloc(16*M);
	show_alloc_mem();
	addr3 = (char*)realloc(addr1, 128*M);
	addr3[127*M] = 42;
	show_alloc_mem();

	return (0);
}
