/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:41:59 by gaubert           #+#    #+#             */
/*   Updated: 2021/11/10 14:58:08 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void	draw_end(t_game *g)
{
	int		x;
	int		y;

	g->won = 1;
	printf("You finished the game with %d moves", g->moves + 1);
	y = 0;
	while (y < g->map_height)
	{
		x = 0;
		while (x < g->map_width)
		{
			if ((x + y) % 2)
				put_img(g, x, y, 'E');
			else
				put_img(g, x, y, 'P');
			mlx_string_put(g->mlx, g->win, x * 64 + 32, y * 64 + 32,
				0x008700af, "GG!");
			x++;
		}
		y++;
	}
	mlx_string_put(g->mlx, g->win, 0, 10,
		0x00aff087, "Press ESC to QUIT !");
}

void	finish(t_game *g)
{
	if (g->coll_count != 0)
	{
		write(1, "You still need to collect onigiris\n", 35);
		g->moves--;
	}
	else
		draw_end(g);
}

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
	update_player_pos(g);
	draw_map(g);
	if (g->map[x + xd + (y + yd) * g->map_width] == 'E')
	{
		finish(g);
	}
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
