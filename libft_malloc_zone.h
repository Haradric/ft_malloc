/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc_zone.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:03:19 by mbraslav          #+#    #+#             */
/*   Updated: 2018/08/27 17:03:19 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_ZONE_H
# define LIBFT_MALLOC_ZONE_H

# include <stddef.h>
# include <stdint.h>

# ifdef DEBUG
#  include <stdio.h>
#  define DEBUG_PRNT(...) do { printf(__VA_ARGS__); fflush(stdout); } while (0)
# else
#  define DEBUG_PRNT(...)
# endif

/*
** Quantum size (Allocation resolution)
** T - tiny, S - small, L - large
*/
# define TBLKSZ 16
# define SBLKSZ 512

/*
** Number of blocks in region
*/
# define TBLKNUM 1 << 16
# define SBLKNUM 1 << 14

/*
** Allocation Size
*/
# define TZONEMAXSZ (1 << 10) - 1
# define SZONEMAXSZ (1 << 17) - 1
# define LZONEMAXSZ SIZE_MAX

/*
** Convert bytes to blocks
*/
# define TB2B(bytes) ((bytes) + TBLKSZ - 1) / TBLKSZ
# define SB2B(bytes) ((bytes) + SBLKSZ - 1) / SBLKSZ

# define FREE_SUCCESS         0
# define FREE_ERR_WRONG_REG  -1
# define FREE_ERR_WRONG_ADDR -2
# define REALLOC_FAILURE      NULL

extern void				*g_zone[3];

# define TREG g_zone[0]
# define SREG g_zone[1]
# define LREG g_zone[2]

typedef struct			s_meta_tiny {
	uint16_t			first:1;
	uint16_t			bytes:15;
}						t_meta_tiny;

typedef struct			s_meta_small {
	uint32_t			first:1;
	uint32_t			bytes:31;
}						t_meta_small;

typedef struct			s_meta_large {
	uint64_t			bytes;
}						t_meta_large;

typedef uint8_t			t_block_tiny[TBLKSZ];
typedef uint8_t			t_block_small[SBLKSZ];

typedef struct			s_zone_tiny {
	t_block_tiny		block[TBLKNUM];
	t_meta_tiny			meta[TBLKNUM];
	size_t				zones;
	struct s_zone_tiny	*next;
}						t_zone_tiny;

typedef struct			s_zone_small {
	t_block_small		block[SBLKNUM];
	t_meta_small		meta[SBLKNUM];
	size_t				zones;
	struct s_zone_small	*next;
}						t_zone_small;

typedef struct			s_zone_large {
	void				*block;
	t_meta_large		meta;
	struct s_zone_large	*next;
}						t_zone_large;

void					*zone_alloc(size_t size);
void					*tiny_alloc(size_t size);
void					*small_alloc(size_t size);
void					*large_alloc(size_t size);

int						zone_free(void *ptr);
int						tiny_free(t_zone_tiny *reg, void *ptr);
int						small_free(t_zone_small *reg, void *ptr);
int						large_free(t_zone_large *reg, void *ptr);

void					*zone_realloc(void *ptr, size_t size);
void					*tiny_realloc(t_zone_tiny *reg, void *ptr, \
																size_t size);
void					*small_realloc(t_zone_small *reg, void *ptr,
																size_t size);
void					*large_realloc(t_zone_large *reg, void *ptr, \
																size_t size);

void					show_reg_tiny(t_zone_tiny *reg, size_t *total, \
																int mode);
void					show_reg_small(t_zone_small *reg, size_t *total, \
																int mode);
void					show_reg_large(t_zone_large *reg, size_t *total, \
																int mode);
void					print_mem_dump(void *addr, size_t len, int mode);

void					*libft_memcpy(void *dst, const void *src, size_t n);
size_t					libft_strlen(const char *s);

void					print_str_ptr(int fd, const char *pre, void *ptr, \
															const char *post);
void					print_str_size(int fd, const char *pre, size_t size, \
															const char *post);
void					print_hex_dump_str(void *ptr, size_t len, \
													size_t offset, char *buff);

#endif
