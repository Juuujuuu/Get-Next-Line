/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmarti <julmarti@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:13:44 by julmarti          #+#    #+#             */
/*   Updated: 2021/05/01 18:39:39 by julmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdio.h>
#define BUFFER_SIZE 27// constante symbolique

// fonction qui read toute la premiere ligne et sauvegarde ce qui a été lu en "trop"
char	*readline(int fd, char *buf)
{
	size_t i;
	size_t j;
	size_t		retread;
	static char *tmp; // variable statique qui conserve l'emplacement de là où nous nous sommes arrêtés de lire lors du dernier appel
	char		*save;

	i = 0;
	j = 0;
	save = malloc(sizeof(char*) * BUFFER_SIZE + 1);
	tmp = malloc(sizeof(char*) * BUFFER_SIZE + 1);
	retread = read(fd, buf, BUFFER_SIZE); // je place le retour de read dans retread, buf contient ce qui a ete lu
	while (retread > 0 && buf[i] != '\n')// si on a lu quelque chose et qu'on rencontre pas la fin d'une ligne
	{
		tmp[i] = buf[i];//  je place ce que j'ai lu dans un char* pour le return
		i++; 
	}
	if (buf[i] == '\n') // si on arrive à un retour à la ligne
	{
		tmp[i] = '\0'; // On a déjà copié ce qui était avant, on a donc qu'a signalé la fin de la copie à tmp en mettant \0
		while (i < retread) // Ce qu'on a lu en plus de la ligne
		{
			save[j] = buf[i]; // on le sauvegarde dans la variable save 
			i++; //j'avance i jusqu'à ce que i = retread, soit buffer_size 
			j++; //j'avance le curseur de save 
		}
	}
	// et si on arrive à EOF : retread sera égal à 0 au prochain appel donc rentre pas dans la boucle
	return (tmp); // je retourne la ligne lue
}

int		get_next_line(int fd, char **line)
{
	int				i;
	char			buf[BUFFER_SIZE + 1]; // contient ce qui est à lire/ a été lu, c'est le même buf que dans la fonction read
	static char		*tmp; // variable statique dont la valeur est issue de la fonction readline
	
	tmp = readline(fd, buf); // on a donc la ligne qui a été lue, pas ce qui suit. Que la ligne. 
	if (!line || fd < 0) //si on a un fd negatif (erreur) ou si read échoue,
		return (-1); // alors return -1 pour signifier une erreur
	//printf("buffer = %s \nfd = %d \nBuffer_size = %d \n", buf, fd, BUFFER_SIZE);
	if (tmp == 0) // si on a atteint la fin du fichier
		return(0);
	if (tmp != 0)
	{
		i = 0;
		*line = malloc(sizeof(char) * BUFFER_SIZE + 1);
		while (tmp[i] != '\0') // tant que j'ai pas fini de lire toute la ligne sauvegardée précédement
		{
			line[0][i] = tmp[i]; // copier la ligne dans line 
			i++; 
		}
		ft_strjoin(*line, buf);// je veux joindre la ligne + ce qui a été lu en trop selon BUFFER_SIZE mais je ne sais pas encore comment faire
		line[0][i] = '\0';// j'ajoute un marqueur qui montre la fin de la ligne lors de mon précédent appel 
	}
	return (1);
}
