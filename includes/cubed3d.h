/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:29:46 by marada            #+#    #+#             */
/*   Updated: 2026/01/19 15:47:48 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED3D_H
# define CUBED3D_H

# include <fcntl.h>
# include "../get_next_line_100/get_next_line.h"
# include "../mlx_linux/mlx.h"

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64

# define W 119
# define A 97
# define S 115
# define D 100

# define PI 3.14159265359

typedef struct s_player
{
	float	x;
	float	y;

	int		key_up;
	int		key_down;
	int		key_left;
	int		key_right;
} t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;

	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;

	char		**map;
} t_game;

//Main
void	put_pixel(int x, int y, int color, t_game *game);
void	draw_square(int x, int y, int size, t_game *game);
void	init_game(t_game *game);

//Player
void	init_player(t_player *player);
void	move_player(t_game *game, t_player *player);
int		key_press(int keycode, t_player *player);
int		key_release(int keycode, t_player *player);

//Raycasting

#endif