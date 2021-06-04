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
	}
	return (*save);
}

// fonction ?
char	*readline(int fd, char *buf, char **save)
{
	size_t		i;
	size_t		retread; 

	i = 0;
	retread = read(fd, buf, BUFFER_SIZE);
	if (retread) 
		*save = savemore(buf, save); 
	return (*save); 
}

// fonction qui retourne -1,0 ou 1 si elle a lu une ligne ou non 
int		get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1]; 
	char			*tmp; 
	static char		*save = NULL; 
	int				i;
	
	if (!line || fd < 0) 
		return (-1); 
	tmp = readline(fd, buf, &save); // tmp contient ce qui a ete lu
	if (tmp == NULL) 
		return(0);
	else 
	{
		line[0] = malloc(sizeof(char) * BUFFER_SIZE + 1); 
		printf("tmp = %s\n", tmp);
		i = 0;
		if (ft_strchr(save,'\n') != NULL) // sinon, je regarde si j'ai une ligne dans ma save. Si oui, je copie save dans line
			{
				while (save[i] != '\n')
				{
					line[0][i] = save[i];
					i++;
				}
			}
	}	
	return (1);
}
// 	printf("buffer = %s \nfd = %d \nBuffer_size = %d \n", buf, fd, BUFFER_SIZE);
//	printf("tmp = %s\n i = %zu \n retread = %zu \n", tmp, i, retread);
// 	printf("save = %s \n", *save);
//	printf("buf = %s \n", buf);