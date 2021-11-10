/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:41:59 by gaubert           #+#    #+#             */
/*   Updated: 2021/11/11 00:17:55 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void	update_player_pos(t_game *g)
{
	int	x;
	int	y;

	y = -1;
	while (++y < g->map_height)
	{
		x = -1;
		while (++x < g->map_width)
		{
			if (g->map[y * (g->map_width) + x] == 'P')
				g->player_pos = (t_coord){x, y};
		}
	}
}

void	update_map(t_game *g, int xd, int yd)
{
	char	*hud;
	char	*tmp;
	int		x;
	int		y;

	x = g->player_pos.x;
	y = g->player_pos.y;
	put_img(g, x + xd, y + yd, g->map[x + xd + (y + yd) * g->map_width]);
	put_img(g, x, y, g->map[x + y * g->map_width]);
	put_img(g, 0, 0, g->map[0]);
	tmp = ft_itoa(g->moves);
	hud = ft_strjoin(tmp, " Moves");
	mlx_string_put(g->mlx, g->win, 10, 10, 0x00ffffff, hud);
	free(hud);
}

void	move(t_game *g, int xd, int yd)
{
	int	x;
	int	y;

	x = g->player_pos.x;
	y = g->player_pos.y;
	if (g->map[x + xd + (y + yd) * g->map_width] == '0')
	{
		g->map[x + xd + (y + yd) * g->map_width] = 'P';
		g->map[x + y * g->map_width] = '0';
	}
	else if (g->map[x + xd + (y + yd) * g->map_width] == 'C')
	{
		g->map[x + xd + (y + yd) * g->map_width] = 'P';
		g->map[x + y * g->map_width] = '0';
		g->coll_count--;
	}
	if (g->map[x + xd + (y + yd) * g->map_width] != '1')
		g->moves++;
	if (g->map[x + xd + (y + yd) * g->map_width] == 'E')
		finish(g);
	if (!g->won)
		update_map(g, xd, yd);
	update_player_pos(g);
}

int	key_hook(int keycode, t_game *g)
{
	(void) g;
	if (keycode == 13 && g->won == 0)
		move(g, 0, -1);
	else if (keycode == 0 && g->won == 0)
		move(g, -1, 0);
	else if (keycode == 1 && g->won == 0)
		move(g, 0, 1);
	else if (keycode == 2 && g->won == 0)
		move(g, 1, 0);
	else if (keycode == 53)
		clean(g);
	return (0);
}
