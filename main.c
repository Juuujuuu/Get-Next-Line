/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmarti <julmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:46:03 by julmarti          #+#    #+#             */
/*   Updated: 2021/03/15 17:04:14 by julmarti         ###   ########.fr       */
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
	int		i;

	line = NULL;
	fd = open("test.txt", O_RDONLY);
	while ((i = get_next_line(fd, &line)) > 0)
	{
		ft_putendl((unsigned char *)line);
		free(line);
		printf("%d\n", i);
	}
	if (line != NULL)
	ft_putendl((unsigned char *)line);
	printf("%d\n", i);
	free(line);
	close(fd);
	system("leaks a.out");
	return (0);
}
