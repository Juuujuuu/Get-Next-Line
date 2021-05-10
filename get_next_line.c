/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmarti <julmarti@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:13:44 by julmarti          #+#    #+#             */
/*   Updated: 2021/05/05 14:21:02 by julmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdio.h>
#define BUFFER_SIZE 2// constante symbolique

// fonction qui sauvegarde ce qui a ete lu en trop 
char 	*savemore(int fd, char *buf)
{
	size_t		i;
	size_t		j;
	size_t		retread;
	static char	*save;

	i = 0;
	j = 0;
	retread = read (fd, buf, BUFFER_SIZE);
	save = malloc(sizeof(char) * BUFFER_SIZE + 1);
	while (i <= retread) // Alors tout ce qu'on a lu en plus de la ligne
	{
		save[j] = buf[i]; // on le sauvegarde dans la variable save 
		i++; //j'avance i jusqu'à ce que i = retread, soit= buffer_size 
		j++; //j'avance le curseur de save 
	}
	return(save);
}

// fonction qui read et retourne la ligne (entièrement ou non). Renvoie a save ce qui n'est pas une ligne
char	*readline(int fd, char *buf)
{
	size_t		i;
	size_t		j;
	size_t		retread;
	static char	*tmp; // conserve l'emplacement là où nous sommes arrêtés de lire lors du dernier appel
	static char *save;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	save = malloc(sizeof(char) * BUFFER_SIZE + 1);
	retread = read(fd, buf, BUFFER_SIZE); // je place le retour de read dans retread, buf contient ce qui a ete lu
	if (retread > 0)
	{
		while (buf[i] != '\n')// si on a lu quelque chose et qu'on rencontre pas la fin d'une ligne
		{
			tmp[i] = buf[i];//  je place ce que j'ai lu dans un char* pour le return
			i++; 
		}
		if (buf[i] == '\n' && i <= retread) // si on arrive à un retour à la ligne et qu'on a lu plus qu'une ligne
			tmp[i] = '\0'; // On signale la fin de la copie en mettant \0
		save[i] = *savemore(fd, buf); // On sauvegarde ce qui a ete lu en trop avec la fonction save

	}
	// et si on arrive à EOF : retread sera égal à 0 au prochain appel donc rentre pas dans la boucle
	return (tmp); // je retourne la ligne lue
}

int		get_next_line(int fd, char **line)
{
	int				i;
	char			buf[BUFFER_SIZE + 1]; // contient ce qui est à lire/ a été lu, c'est le même buf que dans la fonction read
	static char		*tmp; // variable statique dont la valeur est issue de la fonction readline
	static char		*save; // variable issue de la fonction save
	
	tmp = readline(fd, buf); // on a donc la ligne qui a été lue, pas ce qui suit. Que la ligne. 
	if (!line || fd < 0) //si on a un fd negatif (erreur) ou si read échoue,
		return (-1); // alors return -1 pour signifier une erreur
	if (tmp == NULL) // si on a atteint la fin du fichier
		return(0);
	if (tmp != NULL) // si on a lu une ligne 
	{
		i = 0;
		*line = malloc(sizeof(char) * BUFFER_SIZE + 1); // je malloc l'espace pointé par *line
		save = savemore(fd, buf);
		while (line[0][i] != '\n') // Tant que ce que j'ai lu en trop ne constitue pas une ligne
		{
			line[0][i] = save[i]; // copier dans le tableau line
			i++; 
		}
		if (line [0][i] == '\n') // si j ai une ligne 
		ft_strjoin(*line, tmp);// je veux joindre la ligne + ce qui a été lu en trop selon BUFFER_SIZE
		line[0][i] = '\0';// j'ajoute un marqueur qui montre la fin de la ligne lors de mon précédent appel 
	}
	return (1);
}
// 	printf("buffer = %s \nfd = %d \nBuffer_size = %d \n", buf, fd, BUFFER_SIZE);