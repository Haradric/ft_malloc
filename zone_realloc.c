/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:03:19 by mbraslav          #+#    #+#             */
/*   Updated: 2018/08/27 17:03:19 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc_zone.h"

static void	*iter_tiny_regions(void *ptr, size_t size)
{
	t_zone_tiny	*reg;
	void		*ret;

	reg = TREG;
	while (reg)
	{
		if ((ret = tiny_realloc(reg, ptr, size)))
			return (ret);
		reg = reg->next;
	}
	return (REALLOC_FAILURE);
}

static void	*iter_small_regions(void *ptr, size_t size)
{
	t_zone_small	*reg;
	void			*ret;

	reg = SREG;
	while (reg)
	{
		if ((ret = small_realloc(reg, ptr, size)))
			return (ret);
		reg = reg->next;
	}
	return (REALLOC_FAILURE);
}

static void	*iter_large_regions(void *ptr, size_t size)
{
	t_zone_large	*reg;
	void			*ret;

	reg = LREG;
	while (reg)
	{
		if ((ret = large_realloc(reg, ptr, size)))
			return (ret);
		reg = reg->next;
	}
	return (REALLOC_FAILURE);
}

void		*zone_realloc(void *ptr, size_t size)
{
	void	*ret;

	if (ptr == NULL)
		return (REALLOC_FAILURE);
	if ((ret = iter_tiny_regions(ptr, size)))
		return (ret);
	if ((ret = iter_small_regions(ptr, size)))
		return (ret);
	if ((ret = iter_large_regions(ptr, size)))
		return (ret);
	return (REALLOC_FAILURE);
}
