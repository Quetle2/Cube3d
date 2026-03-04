/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:57:43 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/04 21:38:04 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

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
	image->img = NULL;
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
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img.img, &game->img.pixel_bits,
			&game->img.size_line, &game->img.endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
