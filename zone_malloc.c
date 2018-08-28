/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:03:19 by mbraslav          #+#    #+#             */
/*   Updated: 2018/08/27 17:03:19 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft_malloc_zone.h"

void	*zone_alloc(size_t size)
{
	if (!size)
		return (NULL);
	if (size <= TZONEMAXSZ)
	{
		DEBUG_PRNT("using tiny region\n");
		return (tiny_alloc(size));
	}
	else if (size <= SZONEMAXSZ)
	{
		DEBUG_PRNT("using small region\n");
		return (small_alloc(size));
	}
	else if (size <= LZONEMAXSZ)
	{
		DEBUG_PRNT("using large region\n");
		return (large_alloc(size));
	}
	DEBUG_PRNT("sorry, but not today\n");
	return (NULL);
}
