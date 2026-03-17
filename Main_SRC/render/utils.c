/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 04:43:45 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/17 16:32:04 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

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

void	color_pixel(t_game *game, int x, int y)
{
	if (game->theme == 1)
	{
		put_pixel(x, y, (120 << 16) | (0 << 8) | 0, game);
		put_pixel(x, (y + HEIGHT / 2), (25 << 16) | (0 << 8) | 0, game);
	}
	else if (game->theme == 2)
	{
		put_pixel(x, y, (140 << 16) | (40 << 8) | 190, game);
		put_pixel(x, (y + HEIGHT / 2), (20 << 16) | (8 << 8) | 40, game);
	}
	else
	{
		put_pixel(x, y, (50 << 16) | (50 << 8) | 55, game);
		put_pixel(x, (y + HEIGHT / 2), (5 << 16) | (5 << 8) | 5, game);
	}
}
