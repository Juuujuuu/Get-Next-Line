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
#define BUFFER_SIZE 10// constante symbolique

char 	*savemore(char *buf, char **save)
{
	char 	*join;
	size_t	j;
	char	*newsave;

	if (*save == NULL)
		*save = ft_strdup(buf);
	j = ft_strlen(ft_strchr(*save,'\n'));
	if (*save)
	{
		if (ft_strchr(*save,'\n') != NULL) //  si on a une ligne
		{
			newsave = ft_substr(*save, ft_strlen(*save) - j + 1, j);
			free(*save);
			*save = newsave;
		}
		else if (ft_strchr(*save,'\n') == NULL) // si on a pas une ligne
		{
			join = ft_strjoin(*save, buf);
			free(*save);
			*save = join;
		}
	}
	return (*save);
}

void	readline(int fd, char *buf, char **save)
{
	size_t		i;
	size_t		retread;

	i = 0;
	retread = 0;
	printf("saved; %s\n", *save);
	if (!*save || (*save && ft_strchr(*save,'\n') == NULL)) // si je n'ai pas de ligne dans mon save, alors je read
	{
		retread = read(fd, buf, BUFFER_SIZE);
	}
	*save = savemore(buf, save);
}

int		get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	static char		*save = NULL;
	int				i;
	
	printf("JE RENTRE\n");
	if (!line || fd < 0)
		return (-1);
	readline(fd, buf, &save);
	*line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	*line = ft_memset(*line, 0, BUFFER_SIZE + 1);// remplacer par bzero
	i = 0;
	
//	printf("save: %s | buf: %s\n", save, buf);
	if (ft_strchr(save,'\n') != NULL) // sinon, je regarde si j'ai une ligne dans ma save. Si oui, je copie save dans line
	{
		while (save[i] != '\n')
		{
			line[0][i] = save[i];
			i++;
		}
	}
	else if (ft_strchr(buf,'\n') != NULL)
	{
		while (buf[i] != '\n')
		{
			line[0][i] = buf[i];
			i++;
		}
	}
	return (1);
}
// 	printf("save = %s \n", *save);
//	printf("buf = %s \n", buf);