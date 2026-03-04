/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:22:54 by marada            #+#    #+#             */
/*   Updated: 2026/03/04 22:24:22 by marada           ###   ########.fr       */
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

typedef struct s_vars
{
	float	cos_angle;
	float	sin_angle;
	float	dist;
	float	height;
	int		start_y;
	int		end;
	int		hit;
	int		side;
	float	proj_plane;
	int		wall_height;
	int		stepx;
	int		stepy;
	float	sidedistx;
	float	sidedisty;
	float	deltadistx;
	float	deltadisty;
	int		mapx;
	int		mapy;
	int		start_y_original;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	int		color;
	float	ray_x;
	float	ray_y;
}	t_vars;

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	t_vars	vars;

	vars.ray_x = player->x;
	vars.ray_y = player->y;
	vars.deltadisty = 0;
	vars.deltadistx = 0;
	vars.dist = 0;
	vars.cos_angle = cos(start_x);
	vars.sin_angle = sin(start_x);
	vars.mapx = (int)(player->x / BLOCK);
	vars.mapy = (int)(player->y / BLOCK);
	vars.deltadistx = fabs(BLOCK / vars.cos_angle);
	vars.deltadisty = fabs(BLOCK / vars.sin_angle);
	if (vars.cos_angle < 0)
	{
		vars.stepx = -1;
		vars.sidedistx = (player->x - vars.mapx * BLOCK) / fabs(vars.cos_angle);
	}
	else
	{
		vars.stepx = 1;
		vars.sidedistx = ((vars.mapx + 1)
				* BLOCK - player->x) / fabs(vars.cos_angle);
	}
	if (vars.sin_angle < 0)
	{
		vars.stepy = -1;
		vars.sidedisty = (player->y - vars.mapy * BLOCK) / fabs(vars.sin_angle);
	}
	else
	{
		vars.stepy = 1;
		vars.sidedisty = ((vars.mapy + 1)
				* BLOCK - player->y) / fabs(vars.sin_angle);
	}
	vars.hit = 0;
	while (!vars.hit)
	{
		if (vars.sidedistx < vars.sidedisty)
		{
			vars.sidedistx += vars.deltadistx;
			vars.mapx += vars.stepx;
			if (vars.stepx == 1)
				vars.side = 1;
			else
				vars.side = 2;
		}
		else
		{
			vars.sidedisty += vars.deltadisty;
			vars.mapy += vars.stepy;
			if (vars.stepy == 1)
				vars.side = 3;
			else
				vars.side = 4;
		}
		if (ft_strchr("1A", game->map[vars.mapy][vars.mapx]))
			vars.hit = 1;
	}
	if (vars.side == 1 || vars.side == 2)
		vars.dist = (vars.mapx * BLOCK - player->x
				+ (1 - vars.stepx) * BLOCK / 2) / vars.cos_angle;
	else if (vars.side == 3 || vars.side == 4)
		vars.dist = (vars.mapy * BLOCK - player->y
				+ (1 - vars.stepy) * BLOCK / 2) / vars.sin_angle;
	vars.proj_plane = WIDTH / (2 * tan(PI / 6));
	vars.wall_height = (int)((BLOCK / vars.dist) * vars.proj_plane);
	if (vars.hit == 1)
		vars.height = (BLOCK / vars.dist) * (WIDTH / 2);
	else
		vars.height = (FIRE / vars.dist) * (WIDTH / 2);
	(void)vars.height;
	vars.start_y = -vars.wall_height / 2 + HEIGHT / 2;
	vars.start_y_original = vars.start_y;
	if (vars.start_y < 0)
		vars.start_y = 0;
	vars.end = vars.wall_height / 2 + HEIGHT / 2;
	if (vars.end >= HEIGHT)
		vars.end = HEIGHT - 1;
	if (vars.side == 1 || vars.side == 2)
		vars.wall_x = fmod(player->y + vars.dist * vars.sin_angle, BLOCK);
	else
		vars.wall_x = fmod(player->x + vars.dist * vars.cos_angle, BLOCK);
	vars.tex_x = (int)(vars.wall_x / BLOCK * 128);
	while (vars.start_y < vars.end)
	{
		vars.tex_y = (vars.start_y - vars.start_y_original)
			* 128 / vars.wall_height;
		if (vars.side == 1)
			vars.color = game->textures[EAST][vars.tex_y * 128 + vars.tex_x];
		else if (vars.side == 2)
			vars.color = game->textures[WEST][vars.tex_y * 128 + vars.tex_x];
		else if (vars.side == 3)
			vars.color = game->textures[SOUTH][vars.tex_y * 128 + vars.tex_x];
		else
			vars.color = game->textures[NORTH][vars.tex_y * 128 + vars.tex_x];
		put_pixel(i, vars.start_y, vars.color, game);
		vars.start_y++;
	}
	vars.hit = 0;
	while (!touch_bola(vars.ray_x, vars.ray_y, game->bola)
		&& (vars.ray_x <= game->mapinfo.height * 64 && vars.ray_x >= 0)
		&& (vars.ray_y <= game->mapinfo.width * 64 && vars.ray_y >= 0))
	{
		vars.ray_x += vars.cos_angle;
		vars.ray_y += vars.sin_angle;
	}
	if (touch_bola(vars.ray_x, vars.ray_y, game->bola))
		vars.hit = 1;
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
