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

int	draw_loop(t_game *game)
{
	t_player	*player;

	player = &game->player;
	move_player(game, player);
	move_bolas(game);
	clear_image(game);
	draw_square(player->x, player->y, 10, game);
	draw_map(game);
	draw_bolas(game, game->bola);

	float	ray_x = player->x;
	float	ray_y = player->y;

	while (!touch(ray_x, ray_y, game))
	{
		put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x -= player->cos_angle;
		ray_y -= player->sin_angle;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (1);
}
