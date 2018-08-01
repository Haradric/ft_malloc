
#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <stddef.h>

# ifdef DEBUG
# include <stdio.h>
#  define debug(...) printf(__VA_ARGS__)
# else
#  define debug(...)
# endif

# define malloc libft_malloc

void    free(void *ptr);
void    *malloc(size_t size);
void    *realloc(void *ptr, size_t size);

void    show_alloc_mem(void);

# endif

