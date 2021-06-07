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
	size_t	j;
	char	*newsave;

	printf("\t## SaveMore ##\n\n");
	
	if (*save == NULL) 
	{
		printf("\t- Save : strdup\n");
		*save = ft_strdup(buf);
	//	return (*save);
	}
	j = ft_strlen(ft_strchr(*save,'\n'));
	
	printf("\t- J = [%lu]\n", j);
	printf("\t- *Save = [%s]\n", *save);

	//if (*save)
	//{
		printf("\t ## NOT LINE ##\n\n");
		printf("\t- STRJOIN : *save [%s] && [%s]\n", *save, buf);
		join = ft_strjoin(*save, buf);
		free(*save);
		*save = join;
		printf("\t- Save : [%s]\n", *save);
		if (ft_strchr(*save,'\n') != NULL) //  si on a une ligne
		{
			printf("\t ## LINE ##\n\n");
			newsave = ft_substr(*save, ft_strlen(*save) - j + 1, j);
			printf("\t- Substr result [%lu] [%zu]\n", ft_strlen(*save) - j +1, j);
			free(*save);
			*save = newsave;
			printf("\t- Save : [%s]\n", *save);
		}
	
	//}
	//else
	//	printf("\t- Save is NULL (le chat est pas content !)\n");

	printf("\n\t- Final Save : [%s]\n\n", *save);

	return (*save);
}

void	readline(int fd, char *buf, char **save)
{
	size_t		i;
	int			retread;

	i = 0;
	retread = 0;

	printf("\t## ReadLine ##\n\n");

	//if (!*save || (*save && ft_strchr(*save,'\n') == NULL)) // si mon save est null ou si je n'ai pas de ligne dans mon save, alors je read
	retread = read(fd, buf, BUFFER_SIZE);

	printf("\t- ReadLine | Buffer : [%s]\n\n\n", buf);

	*save = savemore(buf, save);
}

int		get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	static char		*save = NULL;
	int				i;
	
	printf("\n\n\n### GET NEXT LINE ###\n\n\n");

	if (!line || fd < 0)
		return (-1);
	readline(fd, buf, &save);

	printf("\t## MALLOC ##\n\n");

	*line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	*line = ft_memset(*line, 0, BUFFER_SIZE + 1);// remplacer par bzero
	i = 0;
	if (ft_strchr(save,'\n') != NULL) // sinon, je regarde si j'ai une ligne dans ma save. Si oui, je copie save dans line
	{
		printf("\t## COPY Save -> Line ##\n\n");
		while (save[i] != '\n')
		{
			line[0][i] = save[i];
			i++;
		}
	}
	else if (ft_strchr(buf,'\n') != NULL)
	{
		printf("\t## COPY Buf -> Line ##\n\n");
		while (buf[i] != '\n')
		{
			line[0][i] = buf[i];
			i++;
		}
	}
	printf("\t- Return 1\n");
	return (1);
}
// 	printf("save = %s \n", *save);
//	printf("buf = %s \n", buf);
//	printf("save: %s | buf: %s\n", save, buf);