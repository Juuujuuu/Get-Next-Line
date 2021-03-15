/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmarti <julmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:13:44 by julmarti          #+#    #+#             */
/*   Updated: 2021/03/15 12:26:05 by julmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#define BUFFER_SIZE 100

int		get_next_line(int fd, char **line)
{
	int		i;
	int		j;
	size_t	retread;
	char	*str_save;
	static char	*tmp;

	i = 0;
	retread = read(fd, *line, BUFFER_SIZE);
	if (!line || fd < 0 || retread < 0 ) //si on a un fd negatif (erreur)  ou si read échoue,
		return (-1); // alors return -1 pour signifier une erreur
	if (retread == 0) // si on a atteint la fin du fichier
		return(0);
	else
	{
		while (retread > 0) // tant que la fonction read lit qqch 
		if (strchr(*line, '\n') != NULL)// si j'ai un \n 
		{
			line[i][j] = str_save[j]; // copier ce qui a ete read dans line 
			tmp = ft_strdup(str_save); // on copie ce qu'il y a apres le \n
			ft_strjoin(str_save, tmp);//join le buffer avec tmp;
		}
		return (1);
	}
}
