/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmarti <julmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:13:44 by julmarti          #+#    #+#             */
/*   Updated: 2021/06/01 16:36:30 by julmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdio.h>

char	*savemore(char **save, char **line) // fonction qui cree une nouvelle string pour garder ce que j'ai pas encore return 
{
	char	*newsave;

	if (ft_strchr(*save, '\n') != NULL)
	{
		newsave = ft_substr(*save, ft_strlen(*line), ft_strlen(*save)); // je recupere ce qu'il reste et je le place dans newsave
		free(*save);
		*save = newsave;
	}
	return (*save);
}

char	*saveless(char *buf, char **save) // fonction qui permet de join avec ce que j'ai obtenu precedemment 
{
	char	*join;

	if (!*save || ft_strchr(*save, '\n') == NULL) // si on a pas une ligne complete 
	{
		join = ft_strjoin(*save, buf);
		free(*save);
		*save = join;
	}
	return (*save);
}

void	savemanage(char *buf, char **save, char **line)
{
	if (ft_strchr(*save, '\n') == NULL) //  si !ligne, join
		*save = saveless(buf, save);
	if (ft_strchr(*save, '\n') != NULL) // si ligne, substr 
	{
		*line = ft_substr(*save, 0, ft_findline(*save) + 1);
		*save = savemore(save, line);
	}
}

char	*get_next_line(int fd)
{
	static char		*save = NULL;
	char			*line;
	char			buf[BUFFER_SIZE + 1];
	int				retread;

	retread = 0;
	if (read(fd, NULL, 0) == -1)
		return (NULL);
	if (!save || (ft_strchr(save, '\n') == NULL)) // si ma save est null ou si je n'ai pas de ligne dans save, alors je read
	{
		retread = read(fd, buf, BUFFER_SIZE);
		if (!retread) // si j'ai deja lu la fin du fichier
			return (NULL);
		save = saveless(buf, &save); // je fais un strjoin dans save de ce que j ai lu
		while (ft_strchr(buf, '\n') == NULL && retread == BUFFER_SIZE) // tant que j'ai pas une ligne complete dans buf et que je suis pas a EOF 
		{
			retread = read(fd, buf, BUFFER_SIZE); //je place le retour de read 
			buf[retread] = '\0'; // je mets un \0 pour signaler la fin de la lecture 
			save = saveless(buf, &save); // je fais un strjoin dans save de ce que j ai lu
		}
		if (retread != BUFFER_SIZE) //si je suis a l'EOF 
			save = saveless("\n", &save); // je rajoute un \n artificiel a save
	}
	savemanage(buf, &save, &line);
	return (line);
}
