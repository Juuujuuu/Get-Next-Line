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

/*
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

int			main(int argc, char **argv)
{
	int		fd;
	char	*line;

	(void)argc;
	line = NULL;
	fd = open(argv[1], O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("\tGNL = %s", line);
		free(line);
	}
	if (line != NULL)
		ft_putendl((unsigned char *)line);
	printf("\tGNL = %s", line);
	free(line);
	close(fd);
//	system("leaks a.out");
	return (0);
}*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int main()
{
    int        fd;
    char    *line;
    int        i;

    i = 1;
    fd = open("test.txt", O_RDWR);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Ligne %d --> %s", i, line);
        free(line);
        i++;
    }
    return (0);
}
