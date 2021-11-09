/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 01:06:07 by gaubert           #+#    #+#             */
/*   Updated: 2021/11/09 02:53:23 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"
#include <stdio.h>
#include "get_next_line.h"

int	count_lines(t_game *g, char *file)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	g->map_width = ft_strlen(line) - 1;
	while (line)
	{
		if (g->map_width != (int)ft_strlen(line) - 1)
		{
			close(fd);
			return (put_error(2));
		}
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (g->map_height = i);
}

void	set_zero(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

int	check_count(t_game *g)
{
	int	x;
	int	y;

	y = -1;
	set_zero(&g->coll_count, &g->exit_count, &g->player_count);
	while (++y < g->map_height)
	{
		x = -1;
		while (++x < g->map_width)
		{
			if (g->map[y * (g->map_width) + x] == 'C')
				g->coll_count++;
			else if (g->map[y * (g->map_width) + x] == 'E')
				g->exit_count++;
			else if (g->map[y * (g->map_width) + x] == 'P')
			{
				g->player_pos = (t_coord){x, y};
				g->player_count++;
			}
		}
	}
	printf("coll_count: %d\n", g->coll_count);printf("exit_count: %d\n", g->exit_count);printf("player_count: %d\n", g->player_count);
	if (g->player_count != 1 || g->coll_count < 1 || g->exit_count < 1)
		return (put_error(5));
	return (0);
}

int	check_map(t_game *g)
{
	int		i;

	i = 0;
	while (i < g->map_height * g->map_width)
	{
		if (g->map[i] != '0' && g->map[i] != '1' && g->map[i] != 'C'
			&& g->map[i] != 'E' && g->map[i] != 'P' && g->map[i] != '\0')
			return (put_error(3));
		i++;
	}
	i = -1;
	while (++i < g->map_width)
	{
		if (g->map[i] != '1'
			|| g->map[g->map_width * g->map_height - 1 - i] != '1')
			return (put_error(4));
	}
	i = -1;
	while (++i < g->map_height)
	{
		if (g->map[i * g->map_width] != '1'
			|| g->map[i * g->map_width + (g->map_width - 1)] != '1')
			return (put_error(4));
	}
	return (check_count(g));
}

int	parse_map(t_game *g, char *file)
{
	int		fd;
	char	*line;
	int		i;
	int		j;

	count_lines(g, file);
	if (g->map_height == -1)
		return (1);
	g->map = malloc(sizeof(char *) * g->map_height);
	fd = open(file, O_RDONLY);
	if (fd == -1 || !g->map)
		return (1);
	line = get_next_line(fd);
	i = -1;
	j = -1;
	while (line)
	{
		printf("%d %s", g->map_height, line);
		while (line[++j] != '\n' && line[j] != '\0')
			g->map[++i] = line[j];
		line = get_next_line(fd);
		j = -1;
	}
	return (check_map(g));
}
