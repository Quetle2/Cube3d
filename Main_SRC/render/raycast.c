/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:29:08 by marada            #+#    #+#             */
/*   Updated: 2026/03/06 01:07:13 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

void	draw_line_init(t_vars *vars, t_player *player, float start_x)
{
	vars->ray_x = player->x;
	vars->ray_y = player->y;
	vars->deltadisty = 0;
	vars->deltadistx = 0;
	vars->dist = 0;
	vars->cos_angle = cos(start_x);
	vars->sin_angle = sin(start_x);
	vars->mapx = (int)(player->x / BLOCK);
	vars->mapy = (int)(player->y / BLOCK);
	vars->deltadistx = fabs(BLOCK / vars->cos_angle);
	vars->deltadisty = fabs(BLOCK / vars->sin_angle);
}

void	draw_line_line(t_vars *vars, t_player *player)
{
	if (vars->cos_angle < 0)
	{
		vars->stepx = -1;
		vars->sidedistx = (player->x - vars->mapx * BLOCK)
			/ fabs(vars->cos_angle);
	}
	else
	{
		vars->stepx = 1;
		vars->sidedistx = ((vars->mapx + 1)
				* BLOCK - player->x) / fabs(vars->cos_angle);
	}
	if (vars->sin_angle < 0)
	{
		vars->stepy = -1;
		vars->sidedisty = (player->y - vars->mapy * BLOCK)
			/ fabs(vars->sin_angle);
	}
	else
	{
		vars->stepy = 1;
		vars->sidedisty = ((vars->mapy + 1)
				* BLOCK - player->y) / fabs(vars->sin_angle);
	}
}

void	draw_line_hit(t_vars *vars, t_game *game)
{
	while (!vars->hit)
	{
		if (vars->sidedistx < vars->sidedisty)
		{
			vars->sidedistx += vars->deltadistx;
			vars->mapx += vars->stepx;
			if (vars->stepx == 1)
				vars->side = 1;
			else
				vars->side = 2;
		}
		else
		{
			vars->sidedisty += vars->deltadisty;
			vars->mapy += vars->stepy;
			if (vars->stepy == 1)
				vars->side = 3;
			else
				vars->side = 4;
		}
		if (ft_strchr("1A", game->map[vars->mapy][vars->mapx]))
			vars->hit = 1;
	}
}

void	draw_line_maishit(t_vars *vars, t_player *player)
{
	if (vars->side == 1 || vars->side == 2)
		vars->dist = (vars->mapx * BLOCK - player->x
				+ (1 - vars->stepx) * BLOCK / 2) / vars->cos_angle;
	else if (vars->side == 3 || vars->side == 4)
		vars->dist = (vars->mapy * BLOCK - player->y
				+ (1 - vars->stepy) * BLOCK / 2) / vars->sin_angle;
	vars->proj_plane = WIDTH / (2 * tan(PI / 6));
	vars->wall_height = (int)((BLOCK / vars->dist) * vars->proj_plane);
	if (vars->hit == 1)
		vars->height = (BLOCK / vars->dist) * (WIDTH / 2);
	else
		vars->height = (FIRE / vars->dist) * (WIDTH / 2);
	vars->start_y = -vars->wall_height / 2 + HEIGHT / 2;
	vars->start_y_original = vars->start_y;
	if (vars->start_y < 0)
		vars->start_y = 0;
	vars->end = vars->wall_height / 2 + HEIGHT / 2;
	if (vars->end >= HEIGHT)
		vars->end = HEIGHT - 1;
	if (vars->side == 1 || vars->side == 2)
		vars->wall_x = fmod(player->y + vars->dist * vars->sin_angle, BLOCK);
	else
		vars->wall_x = fmod(player->x + vars->dist * vars->cos_angle, BLOCK);
	vars->tex_x = (int)(vars->wall_x / BLOCK * 128);
}

void	draw_line_theme(t_vars *vars, t_game *game, int *i)
{
	while (vars->start_y < vars->end)
	{
		vars->tex_y = (vars->start_y - vars->start_y_original)
			* 128 / vars->wall_height;
		if (vars->side == 1)
			vars->color = game->textures[game->theme][EAST][vars->tex_y
				* 128 + vars->tex_x];
		else if (vars->side == 2)
			vars->color = game->textures[game->theme][WEST][vars->tex_y
				* 128 + vars->tex_x];
		else if (vars->side == 3)
			vars->color = game->textures[game->theme][SOTH][vars->tex_y
				* 128 + vars->tex_x];
		else
			vars->color = game->textures[game->theme][NOTH][vars->tex_y
				* 128 + vars->tex_x];
		put_pixel(*i, vars->start_y, vars->color, game);
		vars->start_y++;
	}
}
