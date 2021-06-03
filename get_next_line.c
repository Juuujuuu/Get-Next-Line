/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:13:44 by julmarti          #+#    #+#             */
/*   Updated: 2021/06/01 16:36:30 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdio.h>
#define BUFFER_SIZE 10// constante symbolique

// fonction qui sauvegarde ce qui a ete lu en trop 
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
		j++;
	}
	return (*save);
}

// fonction qui read et retourne la ligne (entièrement ou non). Renvoie a save ce qui n'est pas une ligne
char	*readline(int fd, char *buf, char **save)
{
	size_t		i;
	size_t		retread; 

	i = 0;
	retread = read(fd, buf, BUFFER_SIZE);
	if (retread) 
		*save = savemore(buf, save); 
	return (buf); 
}

// fonction qui retourne -1,0 ou 1 si elle a lu une ligne ou non 
int		get_next_line(int fd, char **line)
{
	int				i;
	char			buf[BUFFER_SIZE + 1]; 
	char			*tmp; 
	static char		*save = NULL; 
	
	if (!line || fd < 0) 
		return (-1); 
	tmp = readline(fd, buf, &save); 
	if (tmp == NULL) 
		return(0);
	else 
	{
		i = 0;
		line[0] = malloc(sizeof(char) * BUFFER_SIZE + 1); 
		if (ft_strchr(tmp, '\n') != NULL) // s'il y a un \n dans mon tmp
			*line = strdup(tmp);
		else if (ft_strchr(save,'\n') != NULL)
			*line = strdup(save);
			printf("line = %s \n", *line);
	}
	return (1);
}
// 	printf("buffer = %s \nfd = %d \nBuffer_size = %d \n", buf, fd, BUFFER_SIZE);
//	printf("tmp = %s\n i = %zu \n retread = %zu \n", tmp, i, retread);
// 	printf("save = %s \n", *save);
//	printf("buf = %s \n", buf);