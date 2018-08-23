
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include "libft_malloc_zone.h"

#define CONVERT_BUFF_SIZE 32

static char *ptr_to_str(void *ptr)
{
    static char buff[CONVERT_BUFF_SIZE + 1] = {0};
    const unsigned short base = 16;
    size_t i = CONVERT_BUFF_SIZE;
    size_t p;
    size_t tmp;

    p = (size_t)ptr;
    while (p > 0)
    {
        tmp = p % base;
        buff[i] = (tmp >= 10) ? tmp - 10 + 'a' : tmp + '0';
        p /= base;
        --i;
    }
    buff[i--] = 'x';
    buff[i] = '0';
    return &buff[i];
}

static char *size_to_str(size_t n)
{
    static char buff[CONVERT_BUFF_SIZE + 1] = {0};
    const unsigned short base = 10;
    size_t i = CONVERT_BUFF_SIZE;
    size_t tmp;

    if (n == 0)
    {
        buff[i] = '0';
        return &buff[i];
    }

    while (n > 0)
    {
        tmp = n % base;
        buff[i] = (tmp >= 10) ? tmp - 10 + 'a' : tmp + '0';
        n /= base;
        --i;
    }
    return &buff[++i];
}

void print_str_ptr(int fd, const char *pre, void *ptr, const char *post)
{
    char *str;

    str = ptr_to_str(ptr);
    write(fd, pre, libft_strlen(pre));
    write(fd, str, libft_strlen(str));
    write(fd, post, libft_strlen(post));
}

void print_str_size(int fd, const char *pre, size_t size, const char *post)
{
    char *str;

    str = size_to_str(size);
    write(fd, pre, libft_strlen(pre));
    write(fd, str, libft_strlen(str));
    write(fd, post, libft_strlen(post));
}
