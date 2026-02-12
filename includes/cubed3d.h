/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:29:46 by marada            #+#    #+#             */
/*   Updated: 2026/02/03 16:34:58 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED3D_H
# define CUBED3D_H

# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include "../get_next_line_100/get_next_line.h"
# include "../mlx_linux/mlx.h"

# define ERR_USAGE "usage: ./cub3d <path/to/map.cub>"

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define SPEED 5

# define W 119
# define A 97
# define S 115
# define D 100
# define F 102
# define Q 113

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define LEFT 65361
# define RIGHT 65363

# define PI 3.14159265359

typedef struct s_bola
{
	float	x;
	float	y;
	float	cos_angle;
	float	sin_angle;
} t_bola;

typedef struct s_player
{
	char	dir;
	float	x;
	float	y;
	float	angle;
	float	cos_angle;
	float	sin_angle;

	int		key_up;
	int		key_down;
	int		key_left;
	int		key_right;

	int		left_rotate;
	int		right_rotate;
} t_player;

typedef struct s_texinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_texinfo;

typedef struct s_mapinfo
{
	int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			index_end_of_map;
}	t_mapinfo;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

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

	t_list		*bola;
	char		**map;
	int			**textures;
	t_mapinfo	mapinfo;
	t_texinfo	texinfo;
} t_game;

//Main
void	put_pixel(int x, int y, int color, t_game *game);
void	init_game(t_game *game);
void	clear_image(t_game *game);

//Parse
int	parse_args(t_game *game, char **av);

//Get Data
int	get_file_data(t_game *game, char **map);

//Create Map
int	create_map(t_game *game, char **file, int i);
size_t	find_biggest_len(t_mapinfo *map, int i);

//Checka Mapa
int	check_map(t_game *game, char **map_tab);

//Error
int	err_msg(char *detail, char *str, int code);

//Free
void	free_tab(void **tab);
void	clean_exit(t_game *game, int code);
int	free_data(t_game *game);

//Player
void	init_player(t_player *player);
void	move_player(t_game *game, t_player *player);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_player *player);

//Raycasting

//Interagir
void	interagir(t_game *game, t_player *player);
void	BOLA_DE_FOGO(t_game *game, t_player *player);

//Draw
void	draw_bolas(t_game *game, t_list *bolas);
void	draw_porta(int x, int y, int size, t_game *game);
void	draw_porta2(int x, int y, int size, t_game *game);
void	draw_square(int x, int y, int size, t_game *game);
void	draw_map(t_game *game);
//Draw2
int		draw_loop(t_game *game);

//Bolas
void	move_bolas(t_game  *game);


#endif