/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmarti <julmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:13:44 by julmarti          #+#    #+#             */
/*   Updated: 2021/03/15 17:05:44 by julmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdio.h>
#define BUFFER_SIZE 12 // constante symbolique 

int		get_next_line(int fd, char **line)
{
	int		i;
	size_t	retread;
	char	*buf;
	static char	*tmp;

	buf = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buf || !line || fd < 0) //si on a un fd negatif (erreur) ou si read échoue,
		return (-1); // alors return -1 pour signifier une erreur
	retread = read(fd, buf, BUFFER_SIZE);
	printf("%s %d %d \n", buf, fd, BUFFER_SIZE);
	if (retread == 0) // si on a atteint la fin du fichier
		return(0);
	else
	{
		i = 0;
		if (ft_strchr(buf, '\n') != NULL)// si j'ai un \n 
		{
			*line[i] = buf[i]; // copier ce qui a ete read dans line 
			tmp = ft_strdup(buf); // on copie ce qu'il y a apres le \n
			ft_strjoin(buf, tmp);//join le buffer avec tmp;
			i++; // j'avance dans buf
		}
		else // si j'ai pas de ligne (car pas de \n)
		{
			*line[i] = buf[i];//je copie le contenu dans line
			i++;
		}
	}
	return (1);
}
