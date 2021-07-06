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

void	readline(int fd, char *buf, char **save);

char	*savemore(char **save, char **line)
{
	char	*newsave;

	if (ft_strchr(*save, '\n') != NULL)
	{
		newsave = ft_substr(*save, ft_strlen(*line), ft_strlen(*save)); // je recupere ce qu'il reste et je le place dans newsave
		free(*save);
		*save = newsave; 
		printf("\tSAVE SUBSTR = %s\n", *save);
	}
	return (*save);
}

char 	*saveless(char *buf, char **save)
{
	char 	*join;

	printf("\t## saveless ##\n");
	if (ft_strchr(*save,'\n') == NULL) // si on a pas une ligne complete 
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
	retread = 0;
	if (!*save || (*save && ft_strchr(*save,'\n') == NULL)) // si mon save est null ou si je n'ai pas de ligne dans mon save, alors je read
		retread = read(fd, buf, BUFFER_SIZE);
}

int		get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	static char		*save = NULL;
	
	printf("\n\n### GET NEXT LINE ###\n\n");
	if (!line || fd < 0)
		return (-1);
	readline(fd, buf, &save);
	if (!*buf && !save)// si je n'ai rien lu et rien dans save, j'ai atteint EOF
		return(0);
	*line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	ft_bzero(*line, BUFFER_SIZE + 1);
	if (!save) // si ma save est vide  
		save = ft_strdup(buf); // je copie ce que j'ai lu directement dans save pour le retravailler ensuite 
	if (ft_strchr(save,'\n') == NULL) //  si on a pasune ligne dans save
		save = saveless(buf, &save); // je joins avec ce que j'ai precedemment 
	else
	{
		*line = ft_substr(save, 0, ft_findline(save) + 1); // je copie la ligne dans line
		save = savemore(&save, line);
	}
	return (1); 
}
// 	printf("save = %s \n", *save);
//	printf("buf = %s \n", buf);
//	printf("save: %s | buf: %s\n", save, buf);