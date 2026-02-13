/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:24:52 by marada            #+#    #+#             */
/*   Updated: 2026/02/05 20:39:29 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

// Meter a ignorar uma cor pa tirar background vai ficar bacano nas portas ou nas bolas de fogos, confia, source confia bro, e so confiar, em frente marujo, YYYYYYYYYYYYYYYAAAAAAAAAAAAAAAAHHHHHHHHHHHH, STEEL BALL RUUUUUUUUUUUUUNNN, mb vou parar. (:
void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	x = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			put_pixel(x, y, 0, game);
	}
}

void	init_mapinfo(t_mapinfo *mapinfo)
{
	mapinfo->fd = 0;
	mapinfo->line_count = 0;
	mapinfo->path = NULL;
	mapinfo->file = NULL;
	mapinfo->height = 0;
	mapinfo->width = 0;
	mapinfo->index_end_of_map = 0;
}

void	init_texture_img(t_game *game, t_img *image, char *path)
{
	image->img =  NULL;
	image->addr = NULL;
	image->pixel_bits = 0;
	image->size_line = 0;
	image->endian = 0;
	image->img = mlx_xpm_file_to_image(game->mlx, path, &game->texinfo.size,
			&game->texinfo.size);
	if (image->img == NULL)
		clean_exit(game, err_msg("mlx", "No imagenss?!", 1));
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	return ;
}

int	*xpm_to_img(t_game *game, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_texture_img(game, &tmp, path);
	buffer = ft_calloc(1,
			sizeof * buffer * game->texinfo.size * game->texinfo.size);
	if (!buffer)
		clean_exit(game, err_msg(NULL, "Malloc e tal", 1));
	y = 0;
	while (y < game->texinfo.size)
	{
		x = 0;
		while (x < game->texinfo.size)
		{
			buffer[y * game->texinfo.size + x]
				= tmp.addr[y * game->texinfo.size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(game->mlx, tmp.img);
	return (buffer);
}

void	init_textures(t_game *game)
{
	game->textures = ft_calloc(5, sizeof * game->textures);
	if (!game->textures)
		clean_exit(game, err_msg(NULL, "Malloc ty shi", 1));
	game->textures[NORTH] = xpm_to_img(game, game->texinfo.north);
	game->textures[SOUTH] = xpm_to_img(game, game->texinfo.south);
	game->textures[EAST] = xpm_to_img(game, game->texinfo.east);
	game->textures[WEST] = xpm_to_img(game, game->texinfo.west);
}

void	init_game(t_game *game)
{
	init_player(&game->player);
	init_mapinfo(&game->mapinfo);
	game->texinfo.north = NULL;
	game->texinfo.south = NULL;
	game->texinfo.west = NULL;
	game->texinfo.east = NULL;
	game->texinfo.floor = 0;
	game->texinfo.ceiling = 0;
	game->texinfo.hex_floor = 0x0;
	game->texinfo.hex_ceiling = 0x0;
	game->texinfo.size = BLOCK;
	game->texinfo.step = 0.0;
	game->texinfo.pos = 0.0;
	game->texinfo.x = 0;
	game->texinfo.y = 0;
	game->bola = NULL;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (err_msg("Usage", ERR_USAGE, 1));
	init_game(&game);
	if (parse_args(&game, av) != 0)
		return (1);
	init_textures(&game);
	
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);

	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);

	return (0);
}
