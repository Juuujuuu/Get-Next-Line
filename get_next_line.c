/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmarti <julmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:13:44 by julmarti          #+#    #+#             */
/*   Updated: 2021/03/11 15:45:46 by julmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	size_t	retread;
	int		i;
	int		j;
	char	*fdline;

	i = 0;
	j = 0;
//	line = (char **)malloc(sizeof(char *) * BUFFER_SIZE);
//	fdline = (char *)malloc(sizeof(char) * ft_strlen(fdline));
	retread = read(fd, *line, BUFFER_SIZE);
	if (!fdline || !line || fd > 0 || retread < 0 ) //si les malloc échouent ou si fd existe ou si read échoue,
		return (-1); // alors return -1 pour signifier un.e erreur 
	if (retread == 0) // si on a atteint la fin du fichier
		return(0);
	else
	{
		while (retread > 0 && fdline[j] != '\0') // tant que read ne retourne pas 0 ça signifie que l'on a pas atteint la fin du fichier
		{
			line[i][j] = fdline[j];// on stocke la ligne lue dans le tableau line
			j++;
		}
		return (1);
	}
}
