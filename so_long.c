/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:04:42 by gaubert           #+#    #+#             */
/*   Updated: 2021/11/09 11:11:55 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"
#include <stdio.h>
#include "get_next_line.h"

void	put_img(t_game *g, int x, int y, char c)
{
	//printf("Put image %c at x %d y %d\n", c, x, y);
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

void	finish(t_game *g)
{
	(void) g;
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

void	move_up(t_game *g)
{
	int	x;
	int	y;

	x = g->player_pos.x;
	y = g->player_pos.y;
	if (g->map[x + (y - 1) * g->map_width] == '0')
	{
		g->map[x + (y - 1) * g->map_width] = 'P';
		g->map[x + y * g->map_width] = '0';
	}
	else if (g->map[x + (y - 1) * g->map_width] == 'C')
	{
		g->map[x + (y - 1) * g->map_width] = 'P';
		g->map[x + y * g->map_width] = '0';
		printf("%d\n", g->coll_count);
		g->coll_count--;
		printf("%d\n", g->coll_count);
	}
	else if (g->map[x + (y - 1) * g->map_width] == 'E')
	{
		finish(g);
	}
	g->moves++;
	update_player_pos(g);
	draw_map(g);
}

void	move_down(t_game *g)
{
	int	x;
	int	y;

	x = g->player_pos.x;
	y = g->player_pos.y;
	if (g->map[x + (y + 1) * g->map_width] == '0')
	{
		g->map[x + (y + 1) * g->map_width] = 'P';
		g->map[x + y * g->map_width] = '0';
	}
	else if (g->map[x + (y + 1) * g->map_width] == 'C')
	{
		g->map[x + (y + 1) * g->map_width] = 'P';
		g->map[x + y * g->map_width] = '0';
		printf("%d\n", g->coll_count);
		g->coll_count--;
		printf("%d\n", g->coll_count);
	}
	else if (g->map[x + (y + 1) * g->map_width] == 'E')
	{
		finish(g);
	}
	g->moves++;
	draw_map(g);
}

int	key_hook(int keycode, t_game *g)
{
	(void) g;
	if (keycode == 13)
	{
		printf("W\n");
		move_up(g);
	}
	else if (keycode == 0)
	{
		printf("A\n");

	}
	else if (keycode == 1)
	{
		printf("S\n");
		move_down(g);
	}
	else if (keycode == 2)
	{
		printf("D\n");
		//move(4, g);
	}
	else if (keycode == 53)
	{
		printf("ESC\n");
	}
	//printf("Hello from key_hook! %d\n", keycode);
	return (0);
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
	mlx_loop(g.mlx);
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