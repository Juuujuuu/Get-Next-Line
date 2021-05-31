/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmarti <julmarti@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:13:44 by julmarti          #+#    #+#             */
/*   Updated: 2021/05/31 21:15:22 by julmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdio.h>
#define BUFFER_SIZE 10// constante symbolique

// fonction qui sauvegarde ce qui a ete lu en trop 
char 	*savemore(size_t i, char *buf)
{	
	char *save;
	size_t j;

	save = malloc(sizeof(char) * BUFFER_SIZE + 1); //A PROTEGER
	j = 0;
	while (buf[i] != '\0') // tant que je ne suis pas arrivée a la fin de ce que j'ai lu
	{
		save[j] = buf[i]; // je copie les éléments en rab dans ma static save, pour le prochain appel
		j++;
		i++;
	}
	save[j] = '\0';
	printf("save = %s \n", save);
	return (save);
}

// fonction qui read et retourne la ligne (entièrement ou non). Renvoie a save ce qui n'est pas une ligne
char	*readline(int fd, char *buf, char **save)
{
	size_t		i;
	size_t		j;
	size_t		k;
	size_t		retread; // je place le retour de read dans retread, buf contient ce qui a ete lu
	char		*tmp;

	i = 0;
	j = 0;
	k = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(*save) + BUFFER_SIZE + 1)); // A PROTEGER
	if (*save != NULL) // si j ai un bout de phrase sauvegarde d'un precedent appel, je ne reread pas tout de suite
	{
		while (save[0][j] != '\0') // alors tant que je n'ai pas fini de tout lire dans save
		{
			tmp[i] = save[0][j]; // je copie save dans tmp 
			i++;
			j++;
		}
	}
	retread = read(fd, buf, BUFFER_SIZE);
	if (retread) // si j arrive a EOF, retread = 0 mais on a quand meme lu qqch
	{
		while (buf[k] != '\n' && buf[k])// si on a lu quelque chose et qu'on rencontre pas la fin d'une ligne
		{
			tmp[i] = buf[k];//  je place ce que j'ai lu dans tmp
			k++;
			i++; 
		}
		tmp[i] = '\0'; // On signale la fin de la copie en mettant \0

		*save = savemore(k, buf); // ce que je lis en plus de ma ligne (apres le \n), je le place dans save avec la fonction savemore
	}

	return (tmp); // je retourne la ligne lue
}

// fonction qui retourne -1,0 ou 1 si elle a lu une ligne ou non 
int		get_next_line(int fd, char **line)
{
	int				i;
	char			buf[BUFFER_SIZE + 1]; // contient ce qui est à lire/ a été lu, c'est le même buf que dans la fonction read
	char			*tmp; // variable  dont la valeur est issue de la fonction readline
	static char		*save = NULL; // variable static dont la valeur evoluera avec la fonction savemore
	 
	
	if (!line || fd < 0) //si on a un fd negatif (erreur) ou si read échoue,
		return (-1); // alors return -1 pour signifier une erreur
	tmp = readline(fd, buf, &save); // on a donc la ligne qui a été lue, pas ce qui suit. Que la ligne.
	if (tmp == NULL) // si on a atteint la fin du fichier
	// return le contenu de line 
		return(0);
	if (tmp != NULL) // si on a lu une ligne 
	{
		i = 0;
		line[0] = malloc(sizeof(char) * BUFFER_SIZE + 1); // je malloc l'espace pointé par *line
		while (tmp[i] != '\0') // tant que je n'ai pas fini de lire la ligne
		{
			line[0][i] = tmp[i]; // je copie la ligne dans le tableau line, qui sera free lors du prochain appel 
			i++; 
		}
		line[0][i] = '\0'; // je mets un /0 pour signaler la fin de la copie 
	}
	return (1);
}
// 	printf("buffer = %s \nfd = %d \nBuffer_size = %d \n", buf, fd, BUFFER_SIZE);
//	printf("save = %s \n", *save);
//	printf("tmp = %s\n i = %zu \n retread = %zu \n", tmp, i, retread);
//	printf("save = %s \n", save);