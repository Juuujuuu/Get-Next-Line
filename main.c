/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmarti <julmarti@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:46:03 by julmarti          #+#    #+#             */
/*   Updated: 2021/07/16 19:13:59 by julmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void ft_putendl(unsigned char *str)
{
	while (*str)
	{
		write(1, &(*str), 1);
		str++;
	}
	write(1, "\n", 1);
}

int			main()
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("\tGNL = %s\n", line);
		free(line);
	}
	if (line != NULL)
	ft_putendl((unsigned char *)line);
	printf("\tGNL = %s\n", line);
	free(line);
	close(fd);
	system("leaks a.out");
	return (0);
}
