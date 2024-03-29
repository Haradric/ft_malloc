
#ifndef LIBFT_MALLOC_ZONE_H
# define LIBFT_MALLOC_ZONE_H

#include <stddef.h>
#include <stdint.h>

# ifdef DEBUG
# include <stdio.h>
#  define debug(...) do \
    { \
        printf(__VA_ARGS__); \
        fflush(stdout); \
    } while (0)
# else
#  define debug(...)
# endif

// Quantum size (Allocation resolution)
// T - tiny, S - small, L - large
# define TBLKSZ 16
# define SBLKSZ 512

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

#define FREE_SUCCESS         0
#define FREE_ERR_WRONG_REG  -1
#define FREE_ERR_WRONG_ADDR -2
#define REALLOC_FAILURE      NULL

typedef struct meta_tiny {
    uint16_t  first:1;
    uint16_t  bytes:15;
} meta_tiny_t;

typedef struct meta_small {
    uint32_t  first:1;
    uint32_t  bytes:31;
} meta_small_t;

typedef struct meta_large {
    uint64_t  bytes;
} meta_large_t;

typedef uint8_t block_tiny_t[TBLKSZ];
typedef uint8_t block_small_t[SBLKSZ];

typedef struct zone_tiny {
    block_tiny_t     block[TBLKNUM];
    meta_tiny_t      meta[TBLKNUM];
    size_t           zones;
    struct zone_tiny *next;
} zone_tiny_t;

typedef struct zone_small {
    block_small_t     block[SBLKNUM];
    meta_small_t      meta[SBLKNUM];
    size_t            zones;
    struct zone_small *next;
} zone_small_t;

typedef struct zone_large {
    void              *block;
    meta_large_t      meta;
    struct zone_large *next;
} zone_large_t;

extern void *zone[3];

#define treg zone[0]
#define sreg zone[1]
#define lreg zone[2]

void    *zone_alloc(size_t size);
void    *tiny_alloc(size_t size);
void    *small_alloc(size_t size);
void    *large_alloc(size_t size);

int     zone_free(void *ptr);
int     tiny_free(zone_tiny_t *reg, void *ptr);
int     small_free(zone_small_t *reg, void *ptr);
int     large_free(zone_large_t *reg, void *ptr);

void    *zone_realloc(void *ptr, size_t size);
void    *tiny_realloc(zone_tiny_t *reg, void *ptr, size_t size);
void    *small_realloc(zone_small_t *reg, void *ptr, size_t size);
void    *large_realloc(zone_large_t *reg, void *ptr, size_t size);

void    show_reg_tiny(zone_tiny_t *reg, size_t *total, int mode);
void    show_reg_small(zone_small_t *reg, size_t *total, int mode);
void    show_reg_large(zone_large_t *reg, size_t *total, int mode);
void    print_mem_dump(void *addr, size_t len, int mode);

void    *libft_memcpy(void *dst, const void *src, size_t n);
size_t  libft_strlen(const char *s);

void    print_str_ptr(int fd, const char *pre, void *ptr, const char *post);
void    print_str_size(int fd, const char *pre, size_t size, const char *post);
void    print_hex_dump_str(void *ptr, size_t len, size_t offset, char *buff);

#endif
