/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 23:23:52 by marada            #+#    #+#             */
/*   Updated: 2026/03/17 15:55:32 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

void	color_fireball(t_game *game, t_vars vars, int i)
{
	if (game->theme == 0)
		put_pixel(i, vars.start_y, 0xB22222, game);
	if (game->theme == 1)
		put_pixel(i, vars.start_y, 0xFFD700, game);
	if (game->theme == 2)
		put_pixel(i, vars.start_y, 0x4F4F4F, game);
	if (game->theme == 3)
		put_pixel(i, vars.start_y, 0x7B68EE, game);
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	t_vars	vars;

	draw_line_init(&vars, player, start_x);
	draw_line_line(&vars, player);
	vars.hit = 0;
	draw_line_hit(&vars, game);
	draw_line_maishit(&vars, player);
	draw_line_theme(&vars, game, &i);
	draw_line_maismore(&vars, game);
	vars.dist = distance(vars.ray_x - player->x, vars.ray_y - player->y);
	vars.height = (FIRE / vars.dist) * (WIDTH / 2);
	vars.start_y = (HEIGHT - vars.height) / 2;
	vars.end = vars.start_y + vars.height;
	if (vars.hit == 1)
	{
		while (vars.start_y <= vars.end)
		{
			color_fireball(game, vars, i);
			vars.start_y++;
		}
	}
}

void	draw_line_maismore(t_vars *vars, t_game *game)
{
	vars->hit = 0;
	while (!touch_bola(vars->ray_x, vars->ray_y, game->bola)
		&& (vars->ray_x <= game->mapinfo.width * 64 && vars->ray_x >= 0)
		&& (vars->ray_y <= game->mapinfo.height * 64 && vars->ray_y >= 0))
	{
		vars->ray_x += vars->cos_angle;
		vars->ray_y += vars->sin_angle;
	}
	if (touch_bola(vars->ray_x, vars->ray_y, game->bola))
		vars->hit = 1;
}
