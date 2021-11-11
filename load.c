/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 01:07:15 by gaubert           #+#    #+#             */
/*   Updated: 2021/11/11 12:53:51 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"
#include <stdio.h>
#include "get_next_line.h"

int	load_assets2(void *mlx, t_game *g)
{
	g->exit.img = mlx_xpm_file_to_image(mlx, "./img/exit.xpm", &g->exit.width,
			&g->exit.height);
	if (!g->exit.img)
		return (1);
	g->exit.addr = mlx_get_data_addr(&g->exit.img, &g->exit.bits_per_pixel,
			&g->exit.width, &g->exit.endian);
	g->empty.img = mlx_xpm_file_to_image(mlx, "./img/empty.xpm",
			&g->empty.width, &g->empty.height);
	if (!g->empty.img)
		return (1);
	g->empty.addr = mlx_get_data_addr(&g->empty.img, &g->empty.bits_per_pixel,
			&g->empty.width, &g->empty.endian);
	g->won = 0;
	g->moves = 0;
	return (0);
}

int	load_assets(void *mlx, t_game *g)
{
	g->wall.img = mlx_xpm_file_to_image(mlx, "./img/wall.xpm", &g->wall.width,
			&g->wall.height);
	if (!g->wall.img)
		return (1);
	g->wall.addr = mlx_get_data_addr(&g->wall.img, &g->wall.bits_per_pixel,
			&g->wall.width, &g->wall.endian);
	g->coll.img = mlx_xpm_file_to_image(mlx, "./img/coll.xpm", &g->coll.width,
			&g->coll.height);
	if (!g->coll.img)
		return (1);
	g->coll.addr = mlx_get_data_addr(&g->coll.img, &g->coll.bits_per_pixel,
			&g->coll.width, &g->coll.endian);
	g->player.img = mlx_xpm_file_to_image(mlx, "./img/player.xpm",
			&g->player.width, &g->player.height);
	if (!g->player.img)
		return (1);
	g->player.addr = mlx_get_data_addr(&g->player.img,
			&g->player.bits_per_pixel, &g->player.width, &g->player.endian);
	return (load_assets2(mlx, g));
}
