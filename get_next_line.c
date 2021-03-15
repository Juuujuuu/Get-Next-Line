/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmarti <julmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:13:44 by julmarti          #+#    #+#             */
/*   Updated: 2021/03/12 16:24:40 by julmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <bsd/string.h>
#define BUFFER_SIZE 100

int		get_next_line(int fd, char **line)
{
	int		i;
	int		j;
	size_t	retread;
	char	*str_save;

	i = 0;
	retread = read(fd, *line, BUFFER_SIZE);
	if (!line || fd > 0 || retread < 0 ) //si les malloc échouent ou si fd existe ou si read échoue,
		return (-1); // alors return -1 pour signifier un.e erreur 
	if (retread == 0) // si on a atteint la fin du fichier
		return(0);
	else
	{
		str_save = strchr(*line, 10); //je place mon curseur sur l'emplacement de la première occurence \n dans line 
		while (retread > 0) // tant que read ne retourne pas 0 ça signifie que l'on a pas atteint la fin du fichier
		{
			
			str_save[j] = line[i][j]; // on stocke la ligne lue dans le tableau line
			j++;
		}
		return (1);
	}
}
