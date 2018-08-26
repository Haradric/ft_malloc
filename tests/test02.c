
#include "libft_malloc.h"

int	main(void)
{
    int		i;
    char	*addr[1024];

    i = 0;
    while (i < 1000)
    {
        addr[i] = (char*)malloc(1504);
        addr[i][0] = 42;
        i++;
    }

    show_alloc_mem();

    i = 0;
    while (i < 1000)
    {
        free(addr[i]);
        i++;
    }
    show_alloc_mem();
    return (0);
}
