/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_dump.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:03:19 by mbraslav          #+#    #+#             */
/*   Updated: 2018/08/27 17:03:19 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft_malloc_zone.h"

#define BYTES 16

void	fill_ascii_buff(void *ptr, char *buff, size_t len)
{
	char	*s;
	size_t	i;

	s = (char *)ptr;
	i = 0;
	while (i < len)
	{
		if ((s[i] < 0x20) || (s[i] > 0x7e))
			buff[i] = '.';
		else
			buff[i] = s[i];
		++i;
	}
	buff[i] = 0;
}

void	print_mem_dump(void *addr, size_t len, int mode)
{
	char	buff[BYTES + 1];
	size_t	i;

	print_str_ptr(STDOUT_FILENO, "", addr, " - ");
	print_str_ptr(STDOUT_FILENO, "", addr + len, " : ");
	print_str_size(STDOUT_FILENO, "", len, " bytes\n");
	if (mode)
	{
		buff[BYTES] = 0;
		i = 0;
		while (i < len)
		{
			if (len - i > BYTES)
			{
				fill_ascii_buff(addr + i, buff, BYTES);
				print_hex_dump_str(addr + i, BYTES, i, buff);
			}
			else
			{
				fill_ascii_buff(addr + i, buff, len - i);
				print_hex_dump_str(addr + i, len - i, i, buff);
			}
			i += BYTES;
		}
	}
}
