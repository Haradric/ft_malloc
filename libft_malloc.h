
#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <stddef.h>

void    *malloc(size_t size);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);

void    show_alloc_mem(void);
void    show_alloc_mem_ex(void);

# endif
