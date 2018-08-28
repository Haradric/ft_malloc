/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_small_alloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:03:19 by mbraslav          #+#    #+#             */
/*   Updated: 2018/08/27 17:03:19 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "libft_malloc_zone.h"

static void		*init_region(void)
{
	void	*reg;

	reg = mmap(0, sizeof(t_zone_small), PROT_READ | PROT_WRITE, \
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (reg == NULL)
	{
		DEBUG_PRNT("can't allocate small region\n");
		return (NULL);
	}
	DEBUG_PRNT("(%p) allocated small region\n", reg);
	return (reg);
}

static size_t	find_free_space(t_zone_small *reg, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = size;
	while (i < SBLKNUM && j != 0)
	{
		if (reg->meta[i].first)
		{
			i += SB2B(reg->meta[i].bytes);
			j = size;
			continue ;
		}
		--j;
		++i;
	}
	return ((j == 0) ? i - size : (size_t)-1);
}

static void		*zone_small_alloc(t_zone_small *reg, size_t size)
{
	size_t	i;

	i = find_free_space(reg, SB2B(size));
	if (i == (size_t)-1)
		return (NULL);
	reg->meta[i].bytes = (uint32_t)size;
	reg->meta[i].first = 1;
	reg->zones += 1;
	return (reg->block[i]);
}

void			*small_alloc(size_t size)
{
	t_zone_small	*reg;
	void			*ret;

	if (!SREG && !(SREG = init_region()))
		return (NULL);
	reg = SREG;
	while (1)
	{
		if ((ret = zone_small_alloc(reg, size)))
		{
			DEBUG_PRNT("(%p) allocated %zu bytes\n", ret, size);
			return (ret);
		}
		if (!reg->next)
			break ;
		reg = reg->next;
	}
	if ((reg->next = init_region()) && \
		(ret = zone_small_alloc(reg->next, size)))
	{
		DEBUG_PRNT("(%p) allocated %zu bytes\n", ret, size);
		return (ret);
	}
	DEBUG_PRNT("can't allocate %zu bytes\n", size);
	return (NULL);
}
