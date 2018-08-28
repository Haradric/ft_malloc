/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:03:19 by mbraslav          #+#    #+#             */
/*   Updated: 2018/08/27 17:03:19 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft_malloc.h"

#define INPUT_SIZE 256
#define STACK_SIZE 1024

static void	*g_ptr[STACK_SIZE] = {0};
static char	g_readbuff[INPUT_SIZE + 1] = {0};

static void	get_line(void)
{
	char	c;
	int		i;

	c = 0;
	i = 0;
	while (c != '\n')
	{
		read(STDIN_FILENO, &c, 1);
		readbuff[i++] = c;
	}
	readbuff[i] = 0;
}

void		call_malloc(void)
{
	size_t		size;
	static int	i = 0;

	get_line();
	size = atoi(readbuff);
	ptr[i] = malloc(size);
	++i;
}

void		call_free(void)
{
	size_t	i;

	get_line();
	i = atoi(readbuff);
	if (i <= 0 || i > STACK_SIZE)
	{
		write(2, "invalid index\n", 14);
		return ;
	}
	free(ptr[i - 1]);
}

void		call_realloc(void)
{
	size_t	i;
	size_t	size;

	get_line();
	i = atoi(readbuff);
	get_line();
	size = atoi(readbuff);
	if (i <= 0 || i > STACK_SIZE)
	{
		write(2, "invalid index\n", 14);
		return ;
	}
	ptr[i - 1] = realloc(ptr[i - 1], size);
}

int			main(void)
{
	while (1)
	{
		get_line();
		if (!strcmp(readbuff, "exit\n"))
			break ;
		else if (!strcmp(readbuff, "malloc\n"))
			call_malloc();
		else if (!strcmp(readbuff, "free\n"))
			call_free();
		else if (!strcmp(readbuff, "realloc\n"))
			call_realloc();
		else if (!strcmp(readbuff, "show\n"))
			show_alloc_mem();
		else if (!strcmp(readbuff, "dump\n"))
			show_alloc_mem_ex();
		else
			write(2, "unknown command\n", 16);
	}
	show_alloc_mem();
	return (0);
}
