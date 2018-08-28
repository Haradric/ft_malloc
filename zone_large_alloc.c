/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_large_alloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:03:19 by mbraslav          #+#    #+#             */
/*   Updated: 2018/08/27 17:03:19 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "libft_malloc_zone.h"

static void	*init_region(void)
{
	void	*reg;

	reg = mmap(0, sizeof(t_zone_large), PROT_READ | PROT_WRITE, \
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (reg == NULL)
	{
		DEBUG_PRNT("can't allocate large region\n");
		return (NULL);
	}
	DEBUG_PRNT("(%p) allocated large region\n", reg);
	return (reg);
}

void		*large_alloc(size_t size)
{
	t_zone_large	*reg;
	t_zone_large	*last;

	if (!(reg = init_region()))
		return (NULL);
	if (!(reg->block = mmap(0, size, PROT_READ | PROT_WRITE, \
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)))
	{
		munmap(reg, sizeof(t_zone_large));
		DEBUG_PRNT("can't allocate %zu bytes\n", size);
		return (NULL);
	}
	reg->meta.bytes = size;
	last = LREG;
	if (last)
	{
		while (last->next)
			last = last->next;
		last->next = reg;
	}
	else
		LREG = reg;
	DEBUG_PRNT("(%p) allocated %zu bytes\n", reg->block, size);
	return (reg->block);
}
