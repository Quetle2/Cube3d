/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 06:00:15 by marada            #+#    #+#             */
/*   Updated: 2026/03/17 16:31:57 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

void	draw_map(t_game *game)
{
	if (game->theme == 0)
		mini_map_color(game->map, game, game->color);
	if (game->theme == 1)
		mini_map_color(game->map, game, game->color);
	if (game->theme == 2)
		mini_map_color(game->map, game, game->color);
	if (game->theme == 3)
		mini_map_color(game->map, game, game->color);
	draw_bolas(game, game->bola);
}

void	draw_ceiling(t_game *game)
{
	int		x;
	int		y;
	int		*ceiling;

	ceiling = game->texinfo.ceiling;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (game->theme == 0)
			{
				put_pixel(x, y, (ceiling[0] << 16)
					| (ceiling[1] << 8) | ceiling[2], game);
			}
			else
				color_pixel(game, x, y);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_game *game)
{
	int	x;
	int	y;
	int	*floor;

	floor = game->texinfo.floor;
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (game->theme == 0)
			{
				put_pixel(x, (y + HEIGHT / 2), (floor[0] << 16)
					| (floor[1] << 8) | floor[2], game);
			}
			else
				color_pixel(game, x, y);
			x++;
		}
		y++;
	}
}

void	draw_mini_mapa(t_game *game)
{
	t_mapinfo	map;
	int			x;
	int			y;
	float		div;

	y = 0;
	map = game->mapinfo;
	div = (BLOCK / 2.5);
	while (y <= map.height * div)
	{
		x = 0;
		while (x <= (map.width - 1) * div)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}
