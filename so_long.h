/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:08:40 by gaubert           #+#    #+#             */
/*   Updated: 2021/11/08 14:38:14 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "mlx/mlx.h"
# include "libft/libft.h"

typedef struct s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_data;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_data		wall;
	t_data		player;
	t_data		coll;
	t_data		exit;
	t_data		empty;
	char		*map;
	int			map_width;
	int			map_height;
	int			coll_count;
	int			mooves_count;
}				t_game;

#endif
