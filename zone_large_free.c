/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_large_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:03:19 by mbraslav          #+#    #+#             */
/*   Updated: 2018/08/27 17:03:19 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "libft_malloc_zone.h"

static void	free_region(t_zone_large *reg)
{
	t_zone_large	*prev;

	if (reg == LREG)
		LREG = reg->next;
	else
	{
		prev = LREG;
		while (prev->next != reg)
			prev = prev->next;
		prev->next = reg->next;
	}
	munmap(reg->block, reg->meta.bytes);
	munmap(reg, sizeof(t_zone_large));
	DEBUG_PRNT("(%p) freed large region\n", reg);
}

int			large_free(t_zone_large *reg, void *ptr)
{
	if (ptr < (void *)reg->block || \
		ptr > ((void *)reg->block + reg->meta.bytes - 1))
		return (FREE_ERR_WRONG_REG);
	if (ptr != reg->block)
		return (FREE_ERR_WRONG_ADDR);
	free_region(reg);
	DEBUG_PRNT("(%p) pointer was freed\n", ptr);
	return (0);
}
