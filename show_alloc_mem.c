/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:03:19 by mbraslav          #+#    #+#             */
/*   Updated: 2018/08/27 17:03:19 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft_malloc_zone.h"

static void	show_alloc_mem_(int mode)
{
	void	*reg;
	size_t	total;

	total = 0;
	reg = TREG;
	while (reg)
	{
		show_reg_tiny(reg, &total, mode);
		reg = ((t_zone_tiny *)reg)->next;
	}
	reg = SREG;
	while (reg)
	{
		show_reg_small(reg, &total, mode);
		reg = ((t_zone_small *)reg)->next;
	}
	reg = LREG;
	while (reg)
	{
		show_reg_large(reg, &total, mode);
		reg = ((t_zone_large *)reg)->next;
	}
	print_str_size(STDOUT_FILENO, "Total: ", total, " bytes\n");
}

void		show_alloc_mem(void)
{
	show_alloc_mem_(0);
}

void		show_alloc_mem_ex(void)
{
	show_alloc_mem_(1);
}
