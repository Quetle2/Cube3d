/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:22:54 by marada            #+#    #+#             */
/*   Updated: 2026/03/25 11:58:05 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

void	mini_map(t_game *game, t_player *player)
{
	draw_mini_mapa(game);
	draw_player((player->x / 2.5), (player->y / 2.5), 0xF5FFFA, game);
	draw_map(game);
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
	if (game->code_map == 1)
		mini_map(game, player);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (1);
}
