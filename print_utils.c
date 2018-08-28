/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:03:19 by mbraslav          #+#    #+#             */
/*   Updated: 2018/08/27 17:03:19 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include "libft_malloc_zone.h"

#define CONVERT_BUFF_SIZE 32

static char	*num_to_hex(size_t n, size_t len)
{
	static char				buff[CONVERT_BUFF_SIZE + 1] = {0};
	const unsigned short	base = 16;
	size_t					i;
	size_t					tmp;

	if (len > CONVERT_BUFF_SIZE)
		return (&buff[CONVERT_BUFF_SIZE]);
	i = 0;
	while (i < CONVERT_BUFF_SIZE)
		buff[i++] = '0';
	while (n > 0)
	{
		tmp = n % base;
		buff[i] = (tmp >= 10) ? tmp - 10 + 'a' : tmp + '0';
		n /= base;
		--i;
	}
	if (len == 0)
		return (&buff[++i]);
	return (&buff[CONVERT_BUFF_SIZE - len + 1]);
}

static char	*size_to_str(size_t n)
{
	static char				buff[CONVERT_BUFF_SIZE + 1] = {0};
	const unsigned short	base = 10;
	size_t					i;
	size_t					tmp;

	i = CONVERT_BUFF_SIZE;
	if (n == 0)
	{
		buff[i] = '0';
		return (&buff[i]);
	}
	while (n > 0)
	{
		tmp = n % base;
		buff[i] = (tmp >= 10) ? tmp - 10 + 'a' : tmp + '0';
		n /= base;
		--i;
	}
	return (&buff[++i]);
}

void		print_str_ptr(int fd, const char *pre, void *ptr, const char *post)
{
	char	*str;

	str = num_to_hex((size_t)ptr, 0);
	write(fd, pre, libft_strlen(pre));
	write(fd, "0x", 2);
	write(fd, str, libft_strlen(str));
	write(fd, post, libft_strlen(post));
}

void		print_str_size(int fd, const char *pre, size_t size, \
															const char *post)
{
	char *str;

	str = size_to_str(size);
	write(fd, pre, libft_strlen(pre));
	write(fd, str, libft_strlen(str));
	write(fd, post, libft_strlen(post));
}

void		print_hex_dump_str(void *ptr, size_t len, size_t offset, char *buff)
{
	char	*str;
	size_t	i;

	str = num_to_hex(offset, 4);
	write(STDOUT_FILENO, "  ", 2);
	write(STDOUT_FILENO, str, 4);
	write(STDOUT_FILENO, " ", 1);
	i = 0;
	while (i < len)
	{
		str = num_to_hex(*(unsigned char*)(ptr + i), 2);
		write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, str, 2);
		++i;
	}
	i = 16 - len;
	while (i--)
		write(STDOUT_FILENO, "   ", 3);
	write(STDOUT_FILENO, "  ", 2);
	write(STDOUT_FILENO, buff, libft_strlen(buff));
	write(STDOUT_FILENO, "\n", 1);
}
