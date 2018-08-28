/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_tiny_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:03:19 by mbraslav          #+#    #+#             */
/*   Updated: 2018/08/27 17:03:19 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "libft_malloc_zone.h"

static void	free_region(t_zone_tiny *reg)
{
	t_zone_tiny	*prev;

	if (reg == TREG && reg->next == NULL)
		return ;
	if (reg == TREG && reg->next != NULL)
		TREG = reg->next;
	else
	{
		prev = TREG;
		while (prev->next != reg)
			prev = prev->next;
		prev->next = reg->next;
		munmap(reg, sizeof(t_zone_tiny));
		DEBUG_PRNT("(%p) freed tiny region\n", reg);
	}
}

int			tiny_free(t_zone_tiny *reg, void *ptr)
{
	size_t	block;

	if (ptr < (void *)&reg->block[0] || \
		ptr > ((void *)&reg->block[TBLKNUM] - 1))
		return (FREE_ERR_WRONG_REG);
	block = (ptr - (void *)&reg->block[0]) / TBLKSZ;
	if (ptr != (void *)&reg->block[block])
		return (FREE_ERR_WRONG_ADDR);
	if (reg->meta[block].first == 0)
		return (FREE_ERR_WRONG_ADDR);
	reg->meta[block].first = 0;
	reg->meta[block].bytes = 0;
	reg->zones -= 1;
	if (!reg->zones)
		free_region(reg);
	DEBUG_PRNT("(%p) pointer was freed\n", ptr);
	return (0);
}
