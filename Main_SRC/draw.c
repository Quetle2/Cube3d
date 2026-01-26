/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 06:00:15 by marada            #+#    #+#             */
/*   Updated: 2026/01/26 14:26:03 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

void	draw_bolas(t_game *game, t_list *bolas)
{
	t_bola	*bola;

	while (bolas)
	{
		bola = (t_bola *)bolas->content;
		draw_square(bola->x, bola->y, 20, game);
		bolas = bolas->next;
	}
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
