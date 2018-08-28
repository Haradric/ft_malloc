/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_small_realloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:03:19 by mbraslav          #+#    #+#             */
/*   Updated: 2018/08/27 17:03:19 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc_zone.h"

static int	is_fit(t_zone_small *reg, size_t index, size_t size)
{
	size_t	end;
	size_t	i;

	end = index + SB2B(size);
	i = index + SB2B(reg->meta[index].bytes);
	if (end > SBLKNUM)
		return (0);
	while (i < end)
	{
		if (reg->meta[i].first == 1)
			return (0);
		++i;
	}
	return (1);
}

static void	*realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	DEBUG_PRNT("(%p) trying to realloc\n", ptr);
	new = zone_alloc(new_size);
	if (!new)
		return (REALLOC_FAILURE);
	libft_memcpy(new, ptr, old_size);
	zone_free(ptr);
	return (new);
}

void		*small_realloc(t_zone_small *reg, void *ptr, size_t size)
{
	size_t	block;

	if (ptr < (void *)&reg->block[0] || \
		ptr > ((void *)&reg->block[SBLKNUM] - 1))
		return (REALLOC_FAILURE);
	block = (ptr - (void *)&reg->block[0]) / SBLKSZ;
	if (ptr != (void *)&reg->block[block])
		return (REALLOC_FAILURE);
	if (reg->meta[block].first == 0)
		return (REALLOC_FAILURE);
	if (is_fit(reg, block, size))
	{
		reg->meta[block].bytes = (uint32_t)size;
		DEBUG_PRNT("(%p) changed size to %zu\n", &reg->block[block], size);
	}
	else
		ptr = realloc(ptr, reg->meta[block].bytes, size);
	return (ptr);
}
