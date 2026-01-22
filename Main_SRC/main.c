/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:24:52 by marada            #+#    #+#             */
/*   Updated: 2026/01/22 19:24:37 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

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

void	draw_porta(int x, int y, int size, t_game *game)
{
	int	i;

	i = -1;
	while (++i < size)
		put_pixel(x + i, y, 0x0AFAFF, game);
	i = -1;
	while (++i < size)
		put_pixel(x, y + i, 0x0AFAFF, game);
	i = -1;
	while (++i < size)
		put_pixel(x + size, y + i, 0x0AFAFF, game);
	i = -1;
	while (++i < size)
		put_pixel(x + i, y + size, 0x0AFAFF, game);
}

void	draw_porta2(int x, int y, int size, t_game *game)
{
	int	i;

	i = -1;
	while (++i < size)
		put_pixel(x + i, y, 0xFF0000, game);
	i = -1;
	while (++i < size)
		put_pixel(x, y + i, 0xFF0000, game);
	i = -1;
	while (++i < size)
		put_pixel(x + size, y + i, 0xFF0000, game);
	i = -1;
	while (++i < size)
		put_pixel(x + i, y + size, 0xFF0000, game);
}

void	draw_square(int x, int y, int size, t_game *game)
{
	int	i;

	i = -1;
	while (++i < size)
		put_pixel(x + i, y, 0x0000FF, game);
	i = -1;
	while (++i < size)
		put_pixel(x, y + i, 0x0000FF, game);
	i = -1;
	while (++i < size)
		put_pixel(x + size, y + i, 0x0000FF, game);
	i = -1;
	while (++i < size)
		put_pixel(x + i, y + size, 0x0000FF, game);
}

void	draw_map(t_game *game)
{
	char	**map;
	int		y;
	int		x;

	x = -1;
	y = -1;
	map = game->map;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, game);
			if (map[y][x] == 'A')
				draw_porta(x * BLOCK, y * BLOCK, BLOCK, game);
			if (map[y][x] == 'F')
				draw_porta2(x * BLOCK, y * BLOCK, BLOCK, game);
		}
	}
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

//TEMPORARIO
char	**get_map(void)
{
	char **map = malloc(sizeof(char *) * 11);
	map[0] = ft_strdup("111111111111111");
	map[1] = ft_strdup("100000000000001");
	map[2] = ft_strdup("100000000000001");
	map[3] = ft_strdup("100010000000001");
	map[4] = ft_strdup("1000000A0000001");
	map[5] = ft_strdup("100000000000001");
	map[6] = ft_strdup("100000000000001");
	map[7] = ft_strdup("100000000000001");
	map[8] = ft_strdup("100000000000001");
	map[9] = ft_strdup("111111111111111");
	map[10] = NULL;
	return (map);
}

void	init_game(t_game *game)
{
	init_player(&game->player);
	game->map = get_map();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	draw_loop(t_game *game)
{
	t_player	*player;

	player = &game->player;
	move_player(game, player);
	clear_image(game);
	draw_square(player->x, player->y, 10, game);
	draw_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (1);
}

int	main(void)
{
	t_game	game;

	init_game(&game);

	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);

	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);

	return (0);
}