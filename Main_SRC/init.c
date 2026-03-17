/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:57:43 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/17 13:37:13 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

void	init_mapinfo(t_mapinfo *mapinfo)
{
	mapinfo->fd = 0;
	mapinfo->path = NULL;
	mapinfo->file = NULL;
	mapinfo->height = 0;
	mapinfo->width = 0;
	mapinfo->index_end_of_map = 0;
}

void	init_texture_img(t_game *game, t_img *image, char *path)
{
	image->img = NULL;
	image->addr = NULL;
	image->pixel_bits = 0;
	image->size_line = 0;
	image->endian = 0;
	image->img = mlx_xpm_file_to_image(game->mlx, path, &game->texinfo.size,
			&game->texinfo.size);
	if (image->img == NULL)
		clean_exit(game, msg_err("mlx", "No imagenss?!", 1));
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	return ;
}

void	init_textures(t_game *game)
{
	game->textures = ft_calloc(16, sizeof * game->textures);
	game->textures[0] = ft_calloc(4, sizeof * *(game->textures));
	game->textures[1] = ft_calloc(4, sizeof * *(game->textures));
	game->textures[2] = ft_calloc(4, sizeof * *(game->textures));
	game->textures[3] = ft_calloc(4, sizeof * *(game->textures));
	game->textures[4] = ft_calloc(1, sizeof * *(game->textures));
	if (!game->textures)
		clean_exit(game, msg_err(NULL, "Malloc ty shi", 1));
	game->textures[0][NOTH] = xpm_to_img(game, game->texinfo.north);
	game->textures[0][SOTH] = xpm_to_img(game, game->texinfo.south);
	game->textures[0][EAST] = xpm_to_img(game, game->texinfo.east);
	game->textures[0][WEST] = xpm_to_img(game, game->texinfo.west);
	game->textures[1][NOTH] = xpm_to_img(game, "textures/sangue_NO.xpm");
	game->textures[1][SOTH] = xpm_to_img(game, "textures/sangue_SO.xpm");
	game->textures[1][EAST] = xpm_to_img(game, "textures/sangue_EA.xpm");
	game->textures[1][WEST] = xpm_to_img(game, "textures/sangue_WE.xpm");
	game->textures[2][NOTH] = xpm_to_img(game, "textures/energia_NO.xpm");
	game->textures[2][SOTH] = xpm_to_img(game, "textures/energia_SO.xpm");
	game->textures[2][EAST] = xpm_to_img(game, "textures/energia_EA.xpm");
	game->textures[2][WEST] = xpm_to_img(game, "textures/energia_WE.xpm");
	game->textures[3][NOTH] = xpm_to_img(game, "textures/morte_NO.xpm");
	game->textures[3][SOTH] = xpm_to_img(game, "textures/morte_SO.xpm");
	game->textures[3][EAST] = xpm_to_img(game, "textures/morte_EA.xpm");
	game->textures[3][WEST] = xpm_to_img(game, "textures/morte_WE.xpm");
	game->textures[4][0] = xpm_to_img(game, "textures/door.xpm");
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
	game->textures = NULL;
	game->theme = 0;
	game->bola = NULL;
	game->map = NULL;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img.img, &game->img.pixel_bits,
			&game->img.size_line, &game->img.endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	init_colors(t_game *game)
{
	game->color.door = ft_calloc(sizeof(int), 4);
	game->color.open = ft_calloc(sizeof(int), 4);
	game->color.square = ft_calloc(sizeof(int), 4);
	game->color.door[0] = 0x8B4513;
	game->color.door[1] = 0x8B0000;
	game->color.door[2] = 0x4B0082;
	game->color.door[3] = 0x363636;
	game->color.open[0] = 0xFF8C00;
	game->color.open[1] = 0xFF0000;
	game->color.open[2] = 0x9400D3;
	game->color.open[3] = 0x4F4F4F;
	game->color.square[0] = 0xF0E68C;
	game->color.square[1] = 0xFF6347;
	game->color.square[2] = 0x9370DB;
	game->color.square[3] = 0xC0C0C0;
}
