/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmarti <julmarti@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:13:44 by julmarti          #+#    #+#             */
/*   Updated: 2021/04/27 10:15:04 by julmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdio.h>
#define BUFFER_SIZE 100 // constante symbolique

// fonction qui read toute la premiere ligne 
char	*readline(int fd, char *buf)
{
	int i;
	size_t		retread;
	static char *tmp; // variable statique qui conserve l'emplacement de là où nous nous sommes arrêtés de lire lors du dernier appel

	i = 0;
	retread = read(fd, buf, BUFFER_SIZE); // je place le retour de read dans retread, buf contient ce qui a ete lu
	buf[retread] = '\0';// pour finir la chaine de caractère lue
	printf("Ce que nous avons lu est : %s", buf);
	while (retread > 0 && buf[i] != '\n')// si on a lu quelque chose et qu'on rencontre pas la fin d'une ligne
	{
		tmp[i] = buf[retread];//  je place ce que j'ai lu dans un char*
		i++; 
	}
	// si on arrive à un \n, on arrête de lire jusqu'au prochain appel et on mémorise la position. Tout ce qui est avant à déjà éte copié. 
	// mais tout ce qui est après devrait peut-être être sauvegardé dans une variable temporaire ?
	// et si on arrive à /0 : retread sera égal à 0 au prochain appel donc rentre pas dans la boucle
	return (tmp); // je retourne la ligne lue
	printf("tmp = %s \n", tmp);
}

int		get_next_line(int fd, char **line)
{
	int				i;
	char			buf[BUFFER_SIZE + 1]; // allocation dynamique + ajoute 1 pour le \0
	static char		*tmp; // variable statique dont la valeur est issue de la fonction readline
	
	if (!line || fd < 0) //si on a un fd negatif (erreur) ou si read échoue,
		return (-1); // alors return -1 pour signifier une erreur
	printf("buffer = %s \nfd = %d \nBuffer_size = %d \n", buf, fd, BUFFER_SIZE);
	if (tmp == 0) // si on a atteint la fin du fichier
		return(0);
	if (tmp != 0)
	{
		i = 0;
		*line = malloc(sizeof(char) * BUFFER_SIZE + 1);
		while (buf[i] != '\n') // tant que  j'ai pas un \n 
		{
			line[0][i] = buf[i]; // copier ce qui a ete read dans line 
			i++; // j'avance dans buf
		}
		tmp = ft_strdup(buf); // on copie ce qu'il y a apres le \n
		printf("buffer = %s \nfd = %d \nBuffer_size = %d \n", buf, fd, BUFFER_SIZE);
		ft_strjoin(*line, tmp);//join le buffer avec tmp;
		line[0][i] = '\0';// j'ajoute un marqueur qui montre la fin de la ligne lors de mon précédent appel 
	}
	return (1);
}
