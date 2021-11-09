/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:04:42 by gaubert           #+#    #+#             */
/*   Updated: 2021/11/09 02:43:59 by gaubert          ###   ########.fr       */
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
	hud = ft_strjoin(tmp, "Moves");
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

int	main(int ac, char **argv)
{
	t_game	game;

	if (ac != 2)
		return (put_error(1));
	if (parse_map(&game, argv[1]))
		return (1);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, game.map_width * 64, game.map_height * 64, "so_long");
	load_assets(game.mlx, &game);
	draw_map(&game);
	mlx_loop(game.mlx);
}

	//t_data	img;
	//mlx_string_put(mlx, mlx_win, 10, 10, 0x008700af, "Hapi");

	//img.img = mlx_new_image(mlx, 2, 2);
	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	//&img.line_length, &img.endian);
	//my_mlx_pixel_put(img.img, 0, 0, 0x00ffffff);
// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int *) dst = color;
// }