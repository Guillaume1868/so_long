/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:08:40 by gaubert           #+#    #+#             */
/*   Updated: 2021/11/04 15:21:58 by gaubert          ###   ########.fr       */
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
	int				x;
	int				y;
}				t_coord;

typedef struct s_game
{
	int				**map;
	int				height;
	int				width;
	t_coord			player;
	int				player_up;
	int				player_down;
	int				player_left;
	int				player_right;
	int				player_move;
	int				player_coll;
	t_coord			exit;
	t_coord			*coll;
	int				count_coll;
	int				count_exit;
	int				count_player;
}				t_game;

typedef struct s_data
{
	void			*mlx;
	void			*mlx_win;
//	t_img			*mlx_img;
	t_game			*game;
//	t_img			*player;
//	t_img			*exit;
//	t_img			*coll;
//	t_img			*wall;
//	t_img			*ground;
}				t_data;


#endif
