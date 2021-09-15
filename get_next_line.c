/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmarti <julmarti@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:13:44 by julmarti          #+#    #+#             */
/*   Updated: 2021/07/17 17:13:48 by julmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdio.h>
//# define BUFFER_SIZE 10000

char	*savemore(char **save, char **line)
{
	char	*newsave;

	newsave = NULL;
	if (ft_strchr(*save, '\n') != NULL)
	{
		newsave = ft_substr(*save, ft_strlen(*line), ft_strlen(*save));
		free(*save);
		*save = newsave;
	}
	return (*save);
}

char	*saveless(char *buf, char **save)
{
	char	*join;

	if ((!*save || ft_strchr(*save, '\n') == NULL) && buf)
	{
		join = ft_strjoin(*save, buf);
		free(*save);
		*save = join;
	}
	return (*save);
}

void	savemanage(char *buf, char **save, char **line)
{
	if (ft_strchr(*save, '\n') == NULL)
		*save = saveless(buf, save);
	if (ft_strchr(*save, '\n') != NULL)
	{
		*line = ft_substr(*save, 0, ft_findline(*save) + 1);
		*save = savemore(save, line);
	}
}

int	readtillend(ssize_t *retread, int fd, char *buf, char **save)
{
	*retread = read(fd, buf, BUFFER_SIZE);
	buf[*retread] = '\0';
	if (!*retread && save)
	{
		free(*save);
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char		*save = NULL;
	char			*line;
	char			buf[BUFFER_SIZE + 1];
	ssize_t			retread;

	retread = 0;
	line = NULL;
	if (read(fd, NULL, 0) == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!save || (ft_strchr(save, '\n') == NULL)) // pour le premier appel et si pas de ligne dispo dans save
	{
		if (readtillend(&retread, fd, buf, &save) == 1)
			return (NULL);
		save = saveless(buf, &save);
		while (ft_strchr(buf, '\n') == NULL && retread == BUFFER_SIZE)
		{
			retread = read(fd, buf, BUFFER_SIZE);
			buf[retread] = '\0';
			save = saveless(buf, &save);
		}
		if (retread != BUFFER_SIZE)
		{	
			//save = saveless("\n", &save);
			line = ft_substr(save, ft_strlen(line), ft_strlen(save));
			//free(save);
		}
	}
	savemanage(buf, &save, &line); // sinon 
	return (line);
}
