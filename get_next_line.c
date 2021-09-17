/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmarti <julmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:46:47 by julmarti          #+#    #+#             */
/*   Updated: 2021/09/17 20:29:33 by julmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

void    savemore(char **line, char **save)
{
    if (ft_strlen(*save) != 0)
    {
        *line = ft_substr(*save, 0, ft_findline(*save) + 1, 0);
        *save = ft_substr(*save, ft_strlen(*line), ft_strlen(*save), 1);
    }
    else
        free (*save);
}

ssize_t    readline(int fd, char **save)
{
    char    buf[BUFFER_SIZE + 1];
    ssize_t ret;

    ret = 1;
    while (ret > 0)
    {
        ret = read(fd, buf, BUFFER_SIZE);
        buf[ret] = 0;
        *save = ft_strjoin(*save, buf);
        if (ft_strchr(*save, '\n') != NULL)
            break ;
    }
    return (ret);
}

char *get_next_line(int fd)
{
    static char *save = NULL;
    char        *line;
    ssize_t     ret;

    line = NULL;
    if (read(fd, NULL, 0) == -1 || BUFFER_SIZE <= 0)
        return (NULL);
    ret = readline(fd, &save);
    savemore(&line, &save);
   if (line == NULL && save == NULL && ret == 0)
       return(NULL);
    return (line);
}