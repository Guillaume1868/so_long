/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:18:04 by gaubert           #+#    #+#             */
/*   Updated: 2021/11/11 12:54:31 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void	draw_end(t_game *g)
{
	int		x;
	int		y;

	g->won = 1;
	printf("You finished the game with %d moves", g->moves);
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
