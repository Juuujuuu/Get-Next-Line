/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:46:03 by julmarti          #+#    #+#             */
/*   Updated: 2021/05/31 17:01:42 by bemoreau         ###   ########.fr       */
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
	int 	j;

	j = 0;
	line = NULL;
	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		if (j++ == 10)
			exit(1);
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
