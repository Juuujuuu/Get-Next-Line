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

char	*savemore(char **save, char **line) // fonction qui cree une nouvelle string pour garder ce que j'ai pas encore return 
{
	char	*newsave;

	printf("\t## SAVEMORE ##\n");
	if (ft_strchr(*save, '\n') != NULL)
	{
		newsave = ft_substr(*save, ft_strlen(*line), ft_strlen(*save)); // je recupere ce qu'il reste et je le place dans newsave
		free(*save);
		*save = newsave; 
		printf("\tSAVE SUBSTR = %s\n", *save);
	}
	return (*save);
}

char 	*saveless(char *buf, char **save) // fonction qui permet de join avec ce que j'ai obtenu precedemment 
{
	char 	*join;

	printf("\t## SAVELESS ##\n");
	if (!*save || ft_strchr(*save,'\n') == NULL) // si on a pas une ligne complete 
	{
		join = ft_strjoin(*save, buf);
		free(*save);
		*save = join;
		printf("\tSAVE STRJOIN = %s\n",*save);
	}
	return (*save);
}

void	readline(int fd, char *buf, char **save)
{
	int		retread;

	printf("\t## READLINE ##\n");
	retread = BUFFER_SIZE;
	printf ("save = %s \n", *save);
	
	if (!*save || (ft_strchr(*save,'\n') == NULL)) // si ma save est null ou si je n'ai pas de ligne dans save, alors je read
	{
		while (ft_strchr(buf,'\n') == NULL && (retread == BUFFER_SIZE))
		{
			retread = read(fd, buf, BUFFER_SIZE);
			printf("RETREAD: %d\nBUF: %s\n", retread, buf);
			buf[retread] = '\0';
			*save = saveless(buf, save);
		}
		if (retread != BUFFER_SIZE)
			*save = saveless("\n", save);
	}
}

char	*get_next_line(int fd)
{
	static char		*save = NULL;
	char			*line;
	char			buf[BUFFER_SIZE + 1];

	printf("\n\n### GET NEXT LINE ###\n\n");
	line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if ( !line || fd < 0)
		return (NULL);
	ft_bzero(line, BUFFER_SIZE + 1);
	readline(fd, buf, &save);
	if (!save)
		save = ft_strdup(buf);
	if (ft_strchr(save,'\n') == NULL) //  si !ligne, join
		save = saveless(buf, &save); 
	if (ft_strchr (save,'\n') != NULL)// si ligne, substr 
	{
		line = ft_substr(save, 0, ft_findline(save) + 1);
		save = savemore(&save, &line);
	}
	return (line); 
}