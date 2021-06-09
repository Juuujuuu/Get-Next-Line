/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmarti <julmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:16:24 by julmarti          #+#    #+#             */
/*   Updated: 2021/06/01 16:18:46 by julmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*newstr;

	newstr = (char *)malloc(sizeof(char) * (len + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			newstr[j] = s[i];
			j++;
		}
		i++;
	}
	newstr[j] = '\0';
	return (newstr);
}

char	*ft_strchr(const char *s, int c)
{
	int	curseur;
	char *str;

	curseur = 0;
	str = (char *)s;
	if (!s)
		return (NULL);
	while (s[curseur])
	{
		if (s[curseur] == c)
			return (&str[curseur]);
		curseur++;
	}
	if (c == '\0')
		return (&str[curseur]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*s2;

	i = 0;
	s2 = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (s2 == NULL)
		return (NULL);
	while (s[i])
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

void    ft_bzero(void *s, size_t n)
{
        size_t          i;
        unsigned char   *str;

        i = 0;
        str = (unsigned char *)s;
        if (n == 0)
                return ;
        while (i < n)
        {
                str[i] = '\0';
                i++;
        }
}