/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:22:54 by marada            #+#    #+#             */
/*   Updated: 2026/01/26 14:25:53 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

int	touch(float px, float py, t_game *game)
{
	int	x = px / BLOCK;
	int y = py / BLOCK;
	if (ft_strchr("1A", game->map[y][x]))
		return 1;
	return 0;
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float	cos_angle = cos(start_x);
	float	sin_angle = sin(start_x);
	float	ray_x = player->x;
	float	ray_y = player->y;

	while (!touch(ray_x, ray_y, game))
	{
		// put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x -= cos_angle;
		ray_y -= sin_angle;
	}

	float	dist = distance(ray_x - player->x, ray_y - player->y);
	float	height = (BLOCK / dist) * (WIDTH / 2);
	int		start_y = (HEIGHT - height) / 2;
	int		end = start_y + height;

	while (start_y < end)
	{
		put_pixel(i, start_y, 255, game);
		start_y++;
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;

	player = &game->player;
	move_player(game, player);
	move_bolas(game);
	clear_image(game);
	draw_square(player->x / 2, player->y / 2, 10, game);
	draw_map(game);
	draw_bolas(game, game->bola);

	float	fraction = PI / 3 / WIDTH;
	float	start_x = player->angle - PI / 6;
	int		i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}

	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (1);
}
