/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:04:42 by gaubert           #+#    #+#             */
/*   Updated: 2021/11/11 00:49:02 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"
#include <stdio.h>
#include "get_next_line.h"

void	put_img(t_game *g, int x, int y, char c)
{
	if (c == '0')
		mlx_put_image_to_window(g->mlx, g->win, g->empty.img, x * 64, y * 64);
	else if (c == '1')
		mlx_put_image_to_window(g->mlx, g->win, g->wall.img, x * 64, y * 64);
	else if (c == 'C')
		mlx_put_image_to_window(g->mlx, g->win, g->coll.img, x * 64, y * 64);
	else if (c == 'E')
		mlx_put_image_to_window(g->mlx, g->win, g->exit.img, x * 64, y * 64);
	else if (c == 'P')
		mlx_put_image_to_window(g->mlx, g->win, g->player.img, x * 64, y * 64);
}

void	draw_map(t_game *g)
{
	int		x;
	int		y;
	char	*hud;
	char	*tmp;

	y = 0;
	while (y < g->map_height)
	{
		x = 0;
		while (x < g->map_width)
		{
			put_img(g, x, y, g->map[x + y * g->map_width]);
			x++;
		}
		y++;
	}
	tmp = ft_itoa(g->moves);
	hud = ft_strjoin(tmp, " Moves");
	mlx_string_put(g->mlx, g->win, 10, 10, 0x00ffffff, hud);
	free(hud);
}

int	put_error(int type)
{
	if (type == 1)
		printf("Error\nPlease specify a .ber map in argument");
	else if (type == 2)
	{
		printf("Error\nInconsistent map width");
		return (-1);
	}
	else if (type == 3)
		printf("Error\nInvalid map char");
	else if (type == 4)
		printf("Error\nMap is not enclosed in walls");
	else if (type == 5)
	{
		printf("Error\n Invalid map, please specify 1 player start position,");
		printf("at least 1 collectible and 1 exit");
	}
	return (1);
}

int	clean(t_game *g)
{
	mlx_destroy_image(g->mlx, g->empty.img);
	mlx_destroy_image(g->mlx, g->player.img);
	mlx_destroy_image(g->mlx, g->coll.img);
	mlx_destroy_image(g->mlx, g->wall.img);
	free(g->map);
	mlx_destroy_window(g->mlx, g->win);
	exit(0);
}

int	main(int ac, char **argv)
{
	t_game	g;

	if (ac != 2)
		return (put_error(1));
	if (parse_map(&g, argv[1]))
		return (1);
	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, g.map_width * 64, g.map_height * 64,
			"so_long");
	load_assets(g.mlx, &g);
	draw_map(&g);
	mlx_key_hook(g.win, key_hook, &g);
	mlx_hook(g.win, 17, 0, clean, &g);
	mlx_loop(g.mlx);
}
