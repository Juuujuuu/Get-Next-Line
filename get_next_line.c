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

char 	*savemore(char *buf, char **save)
{
	char 	*join;
	size_t	start;
	char	*newsave;

	printf("\t## SAVEMORE ##\n");
	if (*save == NULL) 
		*save = ft_strdup(buf);
	start = ft_strlen(ft_strchr(*save,'\n'));
	if (*save)
	{
		if (ft_strchr(*save,'\n') != NULL) //  si on a une ligne
		{
			newsave = ft_substr(*save, ft_strlen(*save) - start + 1, ft_strlen(*save)); // je recupere ma ligne 
			free(*save);
			*save = newsave; // je place la ligne dans save
			printf("\tSAVE SUBSTR = %s\n",*save);
			
		}
		else if (ft_strchr(*save,'\n') == NULL) // si on a pas une ligne complete 
		{
			join = ft_strjoin(*save, buf);
			free(*save);
			*save = join;
			printf("\tSAVE STRJOIN = %s\n",*save);
		}
	}
	return (*save);
}

// fonction pour faire le substr dans save ? 

void	readline(int fd, char *buf, char **save)
{
	int		retread;

	printf("\t## READLINE ##\n");
	retread = 0;
	if (!*save || (*save && ft_strchr(*save,'\n') == NULL)) // si mon save est null ou si je n'ai pas de ligne dans mon save, alors je read
		retread = read(fd, buf, BUFFER_SIZE);
	if (retread == 0 && !*save)
		printf("coucou petite perruche");
	*save = savemore(buf, save);
}

int		get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	static char		*save = NULL;
	int				i;
	
	printf("\n\n### GET NEXT LINE ###\n\n");
	if (!line || fd < 0)
		return (-1);
	readline(fd, buf, &save);
	*line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	ft_bzero(*line, BUFFER_SIZE + 1);
	i = 0;
	if (ft_strchr(save,'\n') != NULL) //  si j'ai une ligne dans ma save. Si oui, je copie save dans line
	{
		while (save[i] != '\n')
		{
			line[0][i] = save[i];
			i++;
		}
	}
	else if (ft_strchr(buf,'\n') != NULL) // sinon, je copie buf dans ma save
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
//	printf("save: %s | buf: %s\n", save, buf);