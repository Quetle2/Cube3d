/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 06:00:15 by marada            #+#    #+#             */
/*   Updated: 2026/03/16 19:29:20 by jobraga-         ###   ########.fr       */
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
		draw_square((bola->x / 2), (bola->y / 2), 8, game);
		bolas = bolas->next;
	}
}

void	draw_porta(int x, int y, int size, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (game->theme == 0)
		{
			put_pixel(x + i, y, 0x0AFAFF, game);
			put_pixel(x, y + i, 0x0AFAFF, game);
			put_pixel(x + size, y + i, 0x0AFAFF, game);
			put_pixel(x + i, y + size, 0x0AFAFF, game);
		}
		i++;
	}
}

void	draw_porta2(int x, int y, int size, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (game->theme == 0)
		{
			put_pixel(x + i, y, 0xFF0000, game);
			put_pixel(x, y + i, 0xFF0000, game);
			put_pixel(x + size, y + i, 0xFF0000, game);
			put_pixel(x + i, y + size, 0xFF0000, game);
		}
		i++;
	}
}

void	draw_square(int x, int y, int size, t_game *game)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (game->theme == 0)
		{
			put_pixel((x + i), y, 0x0000FF, game);
			put_pixel(x, (y + i), 0x0000FF, game);
			put_pixel((x + size), (y + i), 0x0000FF, game);
			put_pixel((x + i), (y + size), 0x0000FF, game);
		}
		i++;
	}
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
				draw_square(x * BLOCK / 2, y * BLOCK / 2, BLOCK / 2, game);
			if (map[y][x] == 'A')
				draw_porta(x * BLOCK / 2, y * BLOCK / 2, BLOCK / 2, game);
			if (map[y][x] == 'F')
				draw_porta2(x * BLOCK / 2, y * BLOCK / 2, BLOCK / 2, game);
		}
	}
}
