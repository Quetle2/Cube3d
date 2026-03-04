/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:22:54 by marada            #+#    #+#             */
/*   Updated: 2026/03/04 23:24:38 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

int	touch_bola(float px, float py, t_list *bolas)
{
	t_bola	*bola;

	while (bolas)
	{
		bola = (t_bola *)(bolas->content);
		if (bola == NULL)
		{
			bolas = bolas->next;
			continue ;
		}
		if ((px >= bola->x && px <= (bola->x + FIRE))
			&& (py >= bola->y && py <= (bola->y + FIRE)))
			return (1);
		bolas = bolas->next;
	}
	return (0);
}

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

void	draw_background(t_game *game)
{
	int	x;
	int	y;
	int	*floor;
	int	*ceiling;

	y = 0;
	floor = game->texinfo.floor;
	ceiling = game->texinfo.ceiling;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, (ceiling[0] << 16)
				| (ceiling[1] << 8) | ceiling[2], game);
			put_pixel(x, (y + HEIGHT / 2), (floor[0] << 16)
				| (floor[1] << 8) | floor[2], game);
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
	draw_background(game);
	draw_square(player->x / 2, player->y / 2, 10, game);
	draw_map(game);
	i = 0;
	start_x = player->angle - PI / 6;
	fraction = PI / 3 / WIDTH;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (1);
}
