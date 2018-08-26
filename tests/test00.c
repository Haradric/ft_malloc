
#include "libft_malloc.h"

int main(void)
{
	int		i;

	i = 0;
	while (i < 1024)
	{
		i++;
	}
	show_alloc_mem();
	return 0;
}
