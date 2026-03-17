/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:22:54 by marada            #+#    #+#             */
/*   Updated: 2026/03/17 16:07:14 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

int	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (ft_strchr("1A", game->map[y][x]))
		return (1);
	return (0);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
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

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = &game->player;
	move_player(game, player);
	move_bolas(game);
	clear_image(game);
	draw_floor(game);
	draw_ceiling(game);
	i = 0;
	start_x = player->angle - PI / 6;
	fraction = PI / 3 / WIDTH;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	draw_mini_mapa(game);
	draw_player((player->x / 2.5), (player->y / 2.5), 0xF5FFFA, game);
	draw_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (1);
}
