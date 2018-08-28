/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_large_realloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:03:19 by mbraslav          #+#    #+#             */
/*   Updated: 2018/08/27 17:03:19 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "libft_malloc_zone.h"

void	*large_realloc(t_zone_large *reg, void *ptr, size_t size)
{
	void	*new;

	if (ptr < (void *)reg->block || \
		ptr > ((void *)reg->block + reg->meta.bytes - 1))
		return (REALLOC_FAILURE);
	if (ptr != reg->block)
		return (REALLOC_FAILURE);
	new = mmap(0, size, PROT_READ | PROT_WRITE, \
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!new)
		return (REALLOC_FAILURE);
	libft_memcpy(new, reg->block, \
			(size < reg->meta.bytes) ? size : reg->meta.bytes);
	munmap(reg->block, reg->meta.bytes);
	DEBUG_PRNT("(%p) reallocated from %p (%zu bytes)\n",
			new, &reg->block, size);
	reg->block = new;
	reg->meta.bytes = size;
	return (reg->block);
}
