/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:29:59 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/17 19:19:17 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

void	draw_fireball(int x, int y, int color, t_game *game)
{
	int		i;
	int		size;

	i = 0;
	size = 6;
	while (i < size)
	{
		put_pixel((x + i), y, color, game);
		put_pixel(x, (y + i), color, game);
		put_pixel((x + size), (y + i), color, game);
		put_pixel((x + i), (y + size), color, game);
		i++;
	}
}

void	draw_player(int x, int y, int color, t_game *game)
{
	int		i;
	int		size;

	i = 0;
	size = 4;
	while (i < size)
	{
		put_pixel((x + i), y, color, game);
		put_pixel(x, (y + i), color, game);
		put_pixel((x + size), (y + i), color, game);
		put_pixel((x + i), (y + size), color, game);
		i++;
	}
}

void	draw_square_map(int x, int y, int color, t_game *game)
{
	int		i;
	float	size;

	i = 0;
	size = (BLOCK / 2.5);
	while (i < size)
	{
		put_pixel((x + i), y, color, game);
		put_pixel(x, (y + i), color, game);
		put_pixel((x + size), (y + i), color, game);
		put_pixel((x + i), (y + size), color, game);
		i++;
	}
}

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
			draw_fireball((bola->x / 2.5), (bola->y / 2.5), 0x8B0000, game);
		if (game->theme == 1)
			draw_fireball((bola->x / 2.5), (bola->y / 2.5), 0xF0E68C, game);
		if (game->theme == 2)
			draw_fireball((bola->x / 2.5), (bola->y / 2.5), 0xC0C0C0, game);
		if (game->theme == 3)
			draw_fireball((bola->x / 2.5), (bola->y / 2.5), 0xA020F0, game);
		bolas = bolas->next;
	}
}

void	mini_map_color(char **map, t_game *game, t_color color)
{
	int		y;
	int		x;
	float	div;

	y = -1;
	div = (BLOCK / 2.5);
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '1')
				draw_square_map(x * div, y * div,
					color.square[game->theme], game);
			if (map[y][x] == 'A')
				draw_square_map(x * div, y * div,
					color.door[game->theme], game);
			if (map[y][x] == 'F')
				draw_square_map(x * div, y * div,
					color.open[game->theme], game);
		}
	}
}
