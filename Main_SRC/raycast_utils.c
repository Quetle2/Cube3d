/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 23:23:52 by marada            #+#    #+#             */
/*   Updated: 2026/03/04 23:24:46 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	t_vars	vars;

	draw_line_init(&vars, player, start_x);
	draw_line_line(&vars, player);
	vars.hit = 0;
	draw_line_hit(&vars, game);
	draw_line_maishit(&vars, player);
	draw_line_maismore(&vars, game, &i);
	vars.dist = distance(vars.ray_x - player->x, vars.ray_y - player->y);
	vars.height = (FIRE / vars.dist) * (WIDTH / 2);
	vars.start_y = (HEIGHT - vars.height) / 2;
	vars.end = vars.start_y + vars.height;
	if (vars.hit == 1)
	{
		while (vars.start_y < vars.end)
		{
			put_pixel(i, vars.start_y, 100, game);
			vars.start_y++;
		}
	}
}
