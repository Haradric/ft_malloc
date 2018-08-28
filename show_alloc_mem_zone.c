/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_zone.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:03:19 by mbraslav          #+#    #+#             */
/*   Updated: 2018/08/27 17:03:19 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft_malloc_zone.h"

void	show_reg_tiny(t_zone_tiny *reg, size_t *total, int mode)
{
	size_t	size;
	size_t	i;

	i = 0;
	print_str_ptr(STDOUT_FILENO, "TINY : ", &reg->block[0], "\n");
	while (i < TBLKNUM)
	{
		if (reg->meta[i].first)
		{
			size = reg->meta[i].bytes;
			print_mem_dump(&reg->block[i], size, mode);
			*total += size;
			i += TB2B(size);
			continue ;
		}
		++i;
	}
}

void	show_reg_small(t_zone_small *reg, size_t *total, int mode)
{
	size_t	size;
	size_t	i;

	i = 0;
	print_str_ptr(STDOUT_FILENO, "SMALL : ", &reg->block[0], "\n");
	while (i < SBLKNUM)
	{
		if (reg->meta[i].first)
		{
			size = reg->meta[i].bytes;
			print_mem_dump(&reg->block[i], size, mode);
			*total += size;
			i += SB2B(size);
			continue ;
		}
		++i;
	}
}

void	show_reg_large(t_zone_large *reg, size_t *total, int mode)
{
	print_str_ptr(STDOUT_FILENO, "LARGE : ", &reg->block, "\n");
	print_mem_dump(reg->block, reg->meta.bytes, mode);
	*total += reg->meta.bytes;
}
