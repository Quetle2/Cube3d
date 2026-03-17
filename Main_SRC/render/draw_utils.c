/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:57:39 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/17 15:59:07 by jobraga-         ###   ########.fr       */
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
