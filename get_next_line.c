/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmarti <julmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:13:44 by julmarti          #+#    #+#             */
/*   Updated: 2021/03/18 17:18:34 by julmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdio.h>
#define BUFFER_SIZE 12 // constante symbolique

// fonction qui read toute la premiere ligne 
char	*readline(int fd, char *buf)
{
	int i;
	size_t		retread;
	static char *tmp;

	i = 0;
	retread = read(fd, buf, BUFFER_SIZE); // je place le retour de read dans retread, buf contient ce qui a ete lu
	while (retread > 0 && buf[i] != '\n')
	{
		tmp[i] = buf[retread];
		i++; 
	}
	return (tmp);
}

int		get_next_line(int fd, char **line)
{
	int				i;
	char			buf[BUFFER_SIZE + 1]; // allocation dynamique + ajoute 1 pour le \0
	static char		*tmp; // variable statique

	if (!line || fd < 0) //si on a un fd negatif (erreur) ou si read échoue,
		return (-1); // alors return -1 pour signifier une erreur
	printf("buffer = %s \n fd = %d \n Buffer_size = %d \n", buf, fd, BUFFER_SIZE);
	if (tmp == 0) // si on a atteint la fin du fichier
		return(0);
	else
	{
		i = 0;
		*line = malloc(sizeof(char) * BUFFER_SIZE + 1);
		while (buf[i] != '\n') // tant que  j'ai pas un \n 
		{
			line[0][i] = buf[i]; // copier ce qui a ete read dans line 
			i++; // j'avance dans buf
		}
		tmp = ft_strdup(buf); // on copie ce qu'il y a apres le \n
		ft_strjoin(*line, tmp);//join le buffer avec tmp;
		line[0][i] = '\0';
	}
	return (1);
}
