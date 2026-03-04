/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:24:52 by marada            #+#    #+#             */
/*   Updated: 2026/03/04 23:50:23 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

// Meter a ignorar uma cor pa tirar background vai ficar bacano nas portas ou nas bolas de fogos, confia, source confia bro, e so confiar, em frente marujo, YYYYYYYYYYYYYYYAAAAAAAAAAAAAAAAHHHHHHHHHHHH, STEEL BALL RUUUUUUUUUUUUUNNN, mb vou parar. (:
void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->img.size_line + x * game->img.pixel_bits / 8;
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

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (err_msg("Usage", ERR_USAGE, 1));
	init_game(&game);
	if (parse_args(&game, av) != 0)
		return (1);
	init_textures(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 1L << 17, close_com, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
