
#ifndef LIBFT_MALLOC_ZONE_H
# define LIBFT_MALLOC_ZONE_H

#include <stdint.h>

#include "libft_malloc.h"

// Quantum size (Allocation resolution)
// T - tiny, S - small, L - large
# define TBLKSZ 16
# define SBLKSZ 512
# define LBLKSZ 4096

// Number of blocks in region
#define TBLKNUM 1 << 16
#define SBLKNUM 2 << 14

// Allocation Size
# define TZONEMAXSZ 1 << 16
# define SZONEMAXSZ 1 << 17

typedef struct meta_tiny {
    uint16_t  first:1;
    uint16_t  bytes:11;
} meta_tiny_t;

// convert bytes to blocks
#define tb2b(bytes) ((bytes) + TBLKSZ - 1) / TBLKSZ
#define sb2b(bytes) ((bytes) + SBLKSZ - 1) / SBLKSZ
#define lb2b(bytes) ((bytes) + LBLKSZ - 1) / LBLKSZ

#define tmeta (*treg).meta
#define tblock (*treg).block

typedef uint32_t block_tiny_t[4];

typedef struct zone_tiny {
    block_tiny_t block[TBLKNUM];
    meta_tiny_t  meta[TBLKNUM];

} zone_tiny_t;

extern zone_tiny_t *treg;

void    *zone_tiny_alloc(size_t size);
void    *zone_small_alloc(size_t size) __attribute((unused));
void    *zone_large_alloc(size_t size) __attribute((unused));

size_t show_alloc_mem_tiny(void);

#endif

