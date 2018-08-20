
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
#define SBLKNUM 1 << 14

// Allocation Size
# define TZONEMAXSZ (1 << 10) - 1
# define SZONEMAXSZ (1 << 17) - 1
# define LZONEMAXSZ SIZE_MAX

// convert bytes to blocks
#define tb2b(bytes) ((bytes) + TBLKSZ - 1) / TBLKSZ
#define sb2b(bytes) ((bytes) + SBLKSZ - 1) / SBLKSZ
#define lb2b(bytes) ((bytes) + LBLKSZ - 1) / LBLKSZ

#define FREE_SUCCESS         0
#define FREE_ERR_WRONG_REG  -1
#define FREE_ERR_WRONG_ADDR -2

typedef struct meta_tiny {
    uint16_t  bytes;
    uint8_t   first:1;
} meta_tiny_t;

typedef struct meta_small {
    uint32_t  bytes:17;
    uint32_t  first:1;
} meta_small_t;

typedef struct meta_large {
    uint64_t  bytes;
} meta_large_t;

typedef uint32_t block_tiny_t[4];
typedef uint32_t block_small_t[16];

typedef struct zone_tiny {
    struct zone_tiny *next;
    block_tiny_t     block[TBLKNUM];
    meta_tiny_t      meta[TBLKNUM];
} zone_tiny_t;

typedef struct zone_small {
    struct zone_small *next;
    block_small_t     block[SBLKNUM];
    meta_small_t      meta[SBLKNUM];
} zone_small_t;

typedef struct zone_large {
    struct zone_large *next;
    void              *block;
    meta_large_t      meta;
} zone_large_t;

extern zone_tiny_t  *treg;
extern zone_small_t *sreg;
extern zone_large_t *lreg;

void    *zone_alloc(size_t size);
void    *tiny_alloc(size_t size);
void    *small_alloc(size_t size);
void    *large_alloc(size_t size);

int     zone_free(void *ptr);
int     tiny_free(zone_tiny_t *reg, void *ptr);
int     small_free(zone_small_t *reg, void *ptr);
int     large_free(zone_large_t *reg, void *ptr);

#endif

