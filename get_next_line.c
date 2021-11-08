/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:34:37 by gaubert           #+#    #+#             */
/*   Updated: 2021/11/08 16:10:46 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

// Return 0 if *stat is NULL
// Return 1 if string *stat contain a \n
// Return 0 if no \n is found.
int	contains_nl(char *stat)
{
	int	i;

	i = 0;
	if (!stat)
		return (0);
	while (stat[i])
	{
		if (stat[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

// Return NULL if stat is NULL or first character of stat string is 0
// Return a new allocated string new_line containing the *stat string
//   until its end or \n with an added \0
// Return NULL if a malloc fails
char	*ft_get_line(char *stat)
{
	int		i;
	char	*new_line;

	i = 0;
	if (!stat || !stat[0])
		return (NULL);
	while (stat[i] && stat[i] != '\n')
		i++;
	i += (stat[i] == '\n');
	new_line = malloc(sizeof(char) * (i + 1));
	if (!new_line)
		return (0);
	i = 0;
	while (stat[i] && stat[i] != '\n')
	{
		new_line[i] = stat[i];
		i++;
	}
	if (stat[i] == '\n')
	{
		new_line[i] = '\n';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

// Return NULL if stat is NULL
// Free stat if it doesnt contain a \n and return NULL
// If it does contain a \n, Allocate a new string containing
//    everything between the \n and \0 and free the static var
//    so the parent fct can set static var address to the new one
// Return
char	*ft_get_start(char *stat)
{
	int		i;
	int		j;
	char	*after_newline;

	i = 0;
	j = 0;
	if (stat == NULL)
		return (NULL);
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == '\0')
		return (ft_free(stat));
	i += stat[i] == '\n';
	after_newline = malloc(sizeof(char) * (ft_strlengnl(stat) - i + 1));
	if (!after_newline)
		return (0);
	while (stat[i])
		after_newline[j++] = stat[i++];
	after_newline[j] = '\0';
	free(stat);
	stat = NULL;
	return (after_newline);
}

char	*get_next_line(int fd)
{
	static char	*stat[FOPEN_MAX];
	char		*buff;
	char		*line;
	int			read_return;

	read_return = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * ((unsigned long)BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (!contains_nl(stat[fd]) && read_return != 0)
	{
		read_return = read(fd, buff, BUFFER_SIZE);
		if (read_return == -1)
			return (ft_free(buff));
		buff[read_return] = '\0';
		stat[fd] = ft_strjoin(stat[fd], buff);
	}
	free(buff);
	line = ft_get_line(stat[fd]);
	stat[fd] = ft_get_start(stat[fd]);
	return (line);
}
