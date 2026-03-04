/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:29:46 by marada            #+#    #+#             */
/*   Updated: 2026/03/04 23:55:35 by marada           ###   ########.fr       */
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
# define FIRE 20
# define SPEED 3

# define W 119
# define A 97
# define S 115
# define D 100
# define E 101
# define F 102
# define Q 113
# define N 110

# define NOTH 0
# define SOTH 1
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
} 				t_bola;

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

	int		gear;
	int		left_rotate;
	int		right_rotate;
} 				t_player;

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
}				t_texinfo;

typedef struct s_mapinfo
{
	int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			index_end_of_map;
}				t_mapinfo;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}				t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;

	char		*data;
	t_img		img;
	t_player	player;

	t_list		*bola;
	char		**map;
	int			**textures;
	t_mapinfo	mapinfo;
	t_texinfo	texinfo;
} 				t_game;

typedef struct s_vars
{
	float	cos_angle;
	float	sin_angle;
	float	dist;
	float	height;
	int		start_y;
	int		end;
	int		hit;
	int		side;
	float	proj_plane;
	int		wall_height;
	int		stepx;
	int		stepy;
	float	sidedistx;
	float	sidedisty;
	float	deltadistx;
	float	deltadisty;
	int		mapx;
	int		mapy;
	int		start_y_original;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	int		color;
	float	ray_x;
	float	ray_y;
}	t_vars;

//bolas.c 
int		check_colisao(t_game *game, t_bola *bola);
void	delete_bolas(t_list **bolas);
void	move_bolas(t_game *game);

//check_map_utils.c
int		check_map_is_at_the_end(t_mapinfo *map);
int		is_a_white_space(char c);
int		check_position_is_valid(t_game *game, char **map_tab);

//check_map.c
int		check_player_position(t_game *game, char **map_tab);
int		check_map_elements(t_game *game, char **map_tab);
int		check_top_or_bottom(char **map_tab, int i, int j);
int		check_map_sides(t_mapinfo *map, char **map_tab);
int		check_map(t_game *game, char **map_tab);

//creat_map_utils.c
size_t	find_biggest_len(t_mapinfo *map, int i);
int		count_map_lines(t_game *game, char **file, int i);
int		fill_map_tab(t_mapinfo *mapinfo, char **map_tab, int index);

//create_map.c
int	get_map_info(t_game *game, char **file, int i);
void	change_space_into_wall(t_game *game);
int	create_map(t_game *game, char **file, int i);

//draw.c
void	draw_bolas(t_game *game, t_list *bolas);
void	draw_porta(int x, int y, int size, t_game *game);
void	draw_porta2(int x, int y, int size, t_game *game);
void	draw_square(int x, int y, int size, t_game *game);
void	draw_map(t_game *game);

//draw2.c
int	draw_loop(t_game *game);
float	distance(float x, float y);
int	touch_bola(float px, float py, t_list *bolas);

//error.c
int		err_msg(char *detail, char *str, int code);

//free.c
int		close_com(t_game *game);
void	free_map(t_game *game);
int		free_data(t_game *game);
void	free_tab(void **tab);
void	clean_exit(t_game *game, int code);

//get_data_utils.c
char	*get_texture_path(char *line, int j);
int		fill_direction_textures(t_texinfo *textures, char *line, int j);
int		no_digit(char *str);

//get_data.c
int		*copy_into_rgb_array(char **rgb_to_convert, int *rgb);
int		*set_rgb_colors(char *line);
int		fill_color_textures(t_game *game, t_texinfo *textures, char *line, int j);
int		ignore_whitespaces_get_info(t_game *game, char **map, int i, int j);
int		get_file_data(t_game *game, char **map);

//init.c
void	init_mapinfo(t_mapinfo *mapinfo);
void	init_texture_img(t_game *game, t_img *image, char *path);
void	init_textures(t_game *game);
void	init_game(t_game *game);

//interagir.c
void	checka_porta(t_game *game, t_player *player, int size_y, int size_x);
void	interagir(t_game *game, t_player *player);
void	bola_de_fogo(t_game *game, t_player *player);
void	gear_shift(t_player *player);

//parse.c
int		is_dir(char *arg);
int		is_cub_file(char *arg);
int		is_xpm_file(char *arg);
void	fill_tab(int row, int column, int i, t_game *game);

//parse_utils.c
int		get_number_of_lines(char *path);
int		check_file(char *arg, int cub);
void	init_player_direlao(t_player *player);
void	parse_data(char *path, t_game *game);
int		parse_args(t_game *game, char **av);

//main.c
void	put_pixel(int x, int y, int color, t_game *game);
void	init_game(t_game *game);
void	clear_image(t_game *game);
int		*xpm_to_img(t_game *game, char *path);


//Player
void	init_player(t_player *player);
void	move_player(t_game *game, t_player *player);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_player *player);
void	move_up(char **map, t_player *player, float cos, float sin);
void	move_down(char **map, t_player *player, float cos, float sin);
void	move_left(char **map, t_player *player, float cos, float sin);
void	move_right(char **map, t_player *player, float cos, float sin);

//Pacima
void	pacima_helper(t_game *game, t_player *player);
void	move_up_helper1(char **map, t_player *player, float cos, float sin);
void	move_up_helper2(char **map, t_player *player, float cos, float sin);
void	move_up_helper3(char **map, t_player *player, float cos, float sin);
void	move_up_helper4(char **map, t_player *player, float cos, float sin);
//Pabaixo
void	pabaixo_helper(t_game *game, t_player *player);
void	move_down_helper1(char **map, t_player *player, float cos, float sin);
void	move_down_helper2(char **map, t_player *player, float cos, float sin);
void	move_down_helper3(char **map, t_player *player, float cos, float sin);
void	move_down_helper4(char **map, t_player *player, float cos, float sin);
//Paesquerda
void	paesquerda_helper(t_game *game, t_player *player);
void	move_left_helper1(char **map, t_player *player, float cos, float sin);
void	move_left_helper2(char **map, t_player *player, float cos, float sin);
void	move_left_helper3(char **map, t_player *player, float cos, float sin);
void	move_left_helper4(char **map, t_player *player, float cos, float sin);
//Padireita
void	padireita_helper(t_game *game, t_player *player);
void	move_right_helper1(char **map, t_player *player, float cos, float sin);
void	move_right_helper2(char **map, t_player *player, float cos, float sin);
void	move_right_helper3(char **map, t_player *player, float cos, float sin);
void	move_right_helper4(char **map, t_player *player, float cos, float sin);

//Raycasting
void	draw_line_maismore(t_vars *vars, t_game *game, int *i);
void	draw_line_maishit(t_vars *vars, t_player *player);
void	draw_line_hit(t_vars *vars, t_game *game);
void	draw_line_line(t_vars *vars, t_player *player);
void	draw_line_init(t_vars *vars, t_player *player, float start_x);
void	draw_line(t_player *player, t_game *game, float start_x, int i);

#endif