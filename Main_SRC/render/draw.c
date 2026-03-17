/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 06:00:15 by marada            #+#    #+#             */
/*   Updated: 2026/03/17 01:42:21 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

void	draw_bolas(t_game *game, t_list *bolas)
{
	t_bola	*bola;

	while (bolas != NULL)
	{
		if (bolas->content == NULL)
		{
			bolas = bolas->next;
			continue ;
		}
		bola = (t_bola *)bolas->content;
		if (game->theme == 0)
			draw_square((bola->x / 2), (bola->y / 2), 6, 0x8B0000, game);
		if (game->theme == 1)
			draw_square((bola->x / 2), (bola->y / 2), 6, 0xF0E68C, game);
		if (game->theme == 2)
			draw_square((bola->x / 2), (bola->y / 2), 6, 0xC0C0C0, game);
		if (game->theme == 3)
			draw_square((bola->x / 2), (bola->y / 2), 6, 0xA020F0, game);
		bolas = bolas->next;
	}
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int		i;

	i = 0;
	while (i < size)
	{
		put_pixel((x + i), y, color, game);
		put_pixel(x, (y + i), color, game);
		put_pixel((x + size), (y + i), color, game);
		put_pixel((x + i), (y + size), color, game);
		i++;
	}
}

void	mini_map_color(char **map, t_game *game, int square, int door, int open)
{
	int		y;
	int		x;
	int		div;

	y = -1;
	div = (BLOCK / 2) - 4;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '1')
				draw_square(x * div, y * div, div, square, game);
			if (map[y][x] == 'A')
				draw_square(x * div, y * div, div, door, game);
			if (map[y][x] == 'F')
				draw_square(x * div, y * div, div, open, game);
		}
	}
}

void	draw_map(t_game *game)
{
	if (game->theme == 0)
		mini_map_color(game->map, game, 0xF0E68C, 0x8B4513, 0xFF8C00);
	if (game->theme == 1)
		mini_map_color(game->map, game, 0xFF6347, 0x8B0000, 0xFF0000);
	if (game->theme == 2)
		mini_map_color(game->map, game, 0x9370DB, 0x4B0082, 0x9400D3);
	if (game->theme == 3)
		mini_map_color(game->map, game, 0xC0C0C0, 0x363636, 0x4F4F4F);
	draw_bolas(game, game->bola);
}
