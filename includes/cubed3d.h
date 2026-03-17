/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:29:46 by marada            #+#    #+#             */
/*   Updated: 2026/03/17 19:06:04 by marada           ###   ########.fr       */
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
}				t_bola;

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
}				t_player;

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

typedef	struct s_colors
{
	int		*square;
	int		*door;
	int		*open;
}		t_color;

typedef struct s_game
{
	void		*mlx;
	void		*win;

	char		*data;
	t_img		img;
	t_player	player;

	t_list		*bola;
	char		**map;
	int			***textures;
	int			theme;
	t_color		color;
	t_mapinfo	mapinfo;
	t_texinfo	texinfo;
}				t_game;

typedef struct s_vars
{
	float	cos_angle;
	float	sin_angle;
	float	dist;
	float	height;
	float	start_y;
	float	end;
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

// ! free_and_error
//error.c
void	fecha_com_msg(t_game *game, char *str, int code);
int		msg_err(char *detail, char *str, int code);

//free_utils.c
void	free_texinfo(t_texinfo *texinfo);
void	free_textures(int ***textures);
void	free_colors(t_color *color);

//free.c
int		close_com(t_game *game);
void	clean_exit(t_game *game, int code);
void	free_tab(void **tab);

// ! movimentounderscoresensual
//pabaixo.c
void	pabaixo_helper(t_game *game, t_player *player);
void	move_down_helper1(char **map, t_player *player, float cos, float sin);
void	move_down_helper2(char **map, t_player *player, float cos, float sin);
void	move_down_helper2(char **map, t_player *player, float cos, float sin);
void	move_down_helper3(char **map, t_player *player, float cos, float sin);
void	move_down_helper4(char **map, t_player *player, float cos, float sin);

//pacima.c
void	pacima_helper(t_game *game, t_player *player);
void	move_up_helper1(char **map, t_player *player, float cos, float sin);
void	move_up_helper2(char **map, t_player *player, float cos, float sin);
void	move_up_helper3(char **map, t_player *player, float cos, float sin);
void	move_up_helper4(char **map, t_player *player, float cos, float sin);

//padireita.c
void	padireita_helper(t_game *game, t_player *player);
void	move_right_helper1(char **map, t_player *player, float cos, float sin);
void	move_right_helper2(char **map, t_player *player, float cos, float sin);
void	move_right_helper3(char **map, t_player *player, float cos, float sin);
void	move_right_helper4(char **map, t_player *player, float cos, float sin);

//paesquerda.c
void	paesquerda_helper(t_game *game, t_player *player);
void	move_left_helper1(char **map, t_player *player, float cos, float sin);
void	move_left_helper2(char **map, t_player *player, float cos, float sin);
void	move_left_helper3(char **map, t_player *player, float cos, float sin);
void	move_left_helper4(char **map, t_player *player, float cos, float sin);

//player_helper.c
void	init_player(t_player *player);
void	key_press_theme(int keycode, t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_player *player);

//player.c
void	move_right(char **map, t_player *player, float cos, float sin);
void	move_left(char **map, t_player *player, float cos, float sin);
void	move_up(char **map, t_player *player, float cos, float sin);
void	move_down(char **map, t_player *player, float cos, float sin);
void	move_player(t_game *game, t_player *player);

// ! parsing
// check_map_utils.c
int		validate_map_end(t_mapinfo *map);
int		is_not_whitespace(char c);
int		validate_player_position(t_game *game, char **map_tab);
int		validate_map_chars(char *line);
int		is_player_char(char player);

//check_map.c
int		validate_full_map(t_game *game, char **map_tab);

//create_map_utils.c
int		populate_map_array(t_mapinfo *mapinfo, char **map_tab, int index);
int		count_map_rows(t_game *game, char **file, int i);

//create_map.c
void	change_space_into_wall(t_game *game);
int		initialize_map(t_game *game, char **file, int i);

//get_data_utils.c
int		assign_texture_path(t_texinfo *info, char *str, int pos);
int		has_no_digits(char *str);
int		*load_texture_pixels(t_game *game, char *file);

//get_data.c
int		parse_file_info(t_game *game, char **map);

//parse_utils.c
int		is_directory(char *arg);
int		is_cub_extension(char *arg);
int		is_xpm_extension(char *arg);
void	fill_map_lines(int row, int column, int i, t_game *game);

//parse.c
int		parse_argumentos(t_game *game, char **av);

// ! render














//bolas.c 
int		check_colisao(t_game *game, t_bola *bola);
void	delete_bolas(t_list **bolas);
void	move_bolas(t_game *game);
void	free_colors(t_color *color);

//creat_map_utils.c
int		count_map_rows(t_game *game, char **file, int i);
int		populate_map_array(t_mapinfo *mapinfo, char **map_tab, int index);

//create_map.c
void	change_space_into_wall(t_game *game);
int		initialize_map(t_game *game, char **file, int i);

//draw.c
void	draw_bolas(t_game *game, t_list *bolas);
void	draw_porta(int x, int y, int size, t_game *game);
void	draw_porta2(int x, int y, int size, t_game *game);
void	draw_square(int x, int y, int size, int color, t_game *game);
void	draw_map(t_game *game);

//draw_utils.c
void	draw_fireball(int x, int y, int color, t_game *game);
void	draw_player(int x, int y, int color, t_game *game);
void	draw_square_map(int x, int y, int color, t_game *game);
void	mini_map_color(char **map, t_game *game, t_color color);
void	draw_floor(t_game *game);
void	draw_ceiling(t_game *game);

//draw2.c
int		draw_loop(t_game *game);
float	distance(float x, float y);
int		touch_bola(float px, float py, t_list *bolas);
void	color_pixel(t_game *game, int x, int y);
void	draw_mini_mapa(t_game *game);
void	draw_player(int x, int y, int color, t_game *game);

//error.c
int		msg_err(char *detail, char *str, int code);
void 	fecha_com_msg(t_game *game, char *str, int code);

//free.c
int		close_com(t_game *game);
void	free_tab(void **tab);
void	clean_exit(t_game *game, int code);
void	free_texinfo(t_texinfo *texinfo);
void	free_textures(int ***textures);

//get_data_utils.c
char	*get_texture_path(char *line, int j);
int		fill_direction_textures(t_texinfo *textures, char *line, int j);
int		no_digit(char *str);

//get_data.c
int		*copy_into_rgb_array(char **rgb_to_convert, int *rgb);
int		*set_rgb_colors(char *line);
int		fill_color_textures(t_game *game, t_texinfo *textures,
			char *line, int j);
int		get_inf(t_game *game, char **map, int i, int j);
int		get_file_inf(t_game *game, char **map);
int		parse_file_info(t_game *game, char **map);


//init.c
void	init_mapinfo(t_mapinfo *mapinfo);
void	init_texture_img(t_game *game, t_img *image, char *path);
void	init_textures(t_game *game);
void	init_game(t_game *game);
void	init_colors(t_game *game);

//interagir.c
void	checka_porta(t_game *game, t_player *player, int size_y, int size_x);
void	interagir(t_game *game, t_player *player);
void	bola_de_fogo(t_game *game, t_player *player);
void	gear_shift(t_player *player);

//parse.c
int		is_directory(char *arg);
int		is_cub_extension(char *arg);
int		is_xpm_extension(char *arg);
void	fill_map_lines(int row, int column, int i, t_game *game);

//parse_utils.c
int		get_number_of_lines(char *path);
int		check_file(char *arg, int cub);
void	parse_data(char *path, t_game *game);
int		parse_argumentos(t_game *game, char **av);

//main.c
void	put_pixel(int x, int y, int color, t_game *game);
void	init_game(t_game *game);
void	clear_image(t_game *game);
int		*xpm_to_img(t_game *game, char *path);
int		*load_texture_pixels(t_game *game, char *file);
int		has_no_digits(char *str);
int		assign_texture_path(t_texinfo *info, char *str, int pos);


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
void	draw_line_maismore(t_vars *vars, t_game *game);
void	draw_line_maishit(t_vars *vars, t_player *player);
void	draw_line_hit(t_vars *vars, t_game *game);
void	draw_line_line(t_vars *vars, t_player *player);
void	draw_line_init(t_vars *vars, t_player *player, float start_x);
void	draw_line_theme(t_vars *vars, t_game *game, int *i);
void	draw_line(t_player *player, t_game *game, float start_x, int i);

#endif