/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:22:54 by marada            #+#    #+#             */
/*   Updated: 2026/03/04 19:30:37 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

int	touch_bola(float px, float py, t_list *bolas)
{
	t_bola *bola;
	while (bolas)
	{
		bola = (t_bola*)(bolas->content);
		if (bola == NULL)
		{
			bolas = bolas->next;
			continue;
		}
		if ((px >= bola->x && px <= (bola->x + FIRE)) && (py >= bola->y && py <= (bola->y + FIRE)))
			return 1;
		bolas = bolas->next;
	}
	return 0;
}

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

int get_side(float cos_angle, float sin_angle, float ray_x, float ray_y)
{
	float	dist_y;
	float	dist_x;
	// int	block_y;
	// int	block_x;


	ray_x += cos_angle;
	ray_y += sin_angle;
	if (cos_angle < 0)
	{
		ray_x -= 1;
		dist_x = ((int)((ray_x + 64) / BLOCK) * 64) - ray_x;
	}
	else
	{
		ray_x += 1;
		dist_x = ((int)((ray_x - 64) / BLOCK) * 64 + 64) - ray_x;
	}
	if (sin_angle < 0)
	{
		ray_y -= 1;
		dist_y = ((int)((ray_y + 64) / BLOCK) * 64) - ray_y;
	}
	else
	{
		ray_y += 1;
		dist_y = ((int)((ray_y - 64) / BLOCK) * 64 + 64) - ray_y;
	}
	if (fabs(dist_y) > fabs(dist_x))
	{
		if (dist_x < 0)
			return (WEST);
		else
			return (EAST);
	}
	if (fabs(dist_y) < fabs(dist_x))
	{
		if (dist_y < 0)
			return (NORTH);
		else
			return (SOUTH);
	}
	return (5);
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float	cos_angle;
	float	sin_angle;
	float	dist = 0;
	float	height;
	int		start_y;
	int		end;
	int		hit;
	int		side;
	float	proj_plane;
	int		wall_height;
	int		stepX;
	int		stepY;
	float	sideDistX;
	float	sideDistY;
	float	deltaDistX = 0;
	float	deltaDistY = 0;
	int		mapX;
	int		mapY;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);

	mapX = (int)(player->x / BLOCK);
	mapY = (int)(player->y / BLOCK);

	deltaDistX = fabs(BLOCK / cos_angle);
	deltaDistY = fabs(BLOCK / sin_angle);

	if (cos_angle < 0)
	{
		stepX = -1;
		sideDistX = (player->x - mapX * BLOCK) / fabs(cos_angle);
	}
	else
	{
		stepX = 1;
		sideDistX = ((mapX + 1) * BLOCK - player->x) / fabs(cos_angle);
	}
	if (sin_angle < 0)
	{
		stepY = -1;
		sideDistY = (player->y - mapY * BLOCK) / fabs(sin_angle);
	}
	else
	{
		stepY = 1;
		sideDistY = ((mapY + 1) * BLOCK - player->y) / fabs(sin_angle);
	}
	hit = 0;
	while (!hit)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			if (stepX == 1)
				side = 1;
			else
				side = 2;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			if (stepY == 1)
				side = 3;
			else
				side = 4;
		}
		if (game->map[mapY][mapX] == '1')
			hit = 1;
	}
	if (side == 1 || side == 2)
		dist = (mapX * BLOCK - player->x + (1 - stepX) * BLOCK / 2) / cos_angle;
	else if (side == 3 || side == 4)
		dist = (mapY * BLOCK - player->y + (1 - stepY) * BLOCK / 2) / sin_angle;
	proj_plane = WIDTH / (2 * tan(PI / 6));
	wall_height = (int)((BLOCK / dist) * proj_plane);
	if (hit == 1)
		height = (BLOCK / dist) * (WIDTH / 2);
	else
		height = (FIRE / dist) * (WIDTH / 2);
	(void)height;
	start_y = -wall_height / 2 + HEIGHT / 2;
	int		start_y_original;
	start_y_original = start_y;
	if (start_y < 0)
		start_y = 0;
	end = wall_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;

	//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
	double	wall_x;
	int		tex_x;
	if (side == 1 || side == 2)
    	wall_x = fmod(player->y + dist * sin_angle, BLOCK);
	else
    	wall_x = fmod(player->x + dist * cos_angle, BLOCK);
	tex_x = (int)(wall_x / BLOCK * 128);
	int		tex_y;
	int		color;
	while (start_y < end)
	{
    	tex_y = (start_y - start_y_original) * 128 / wall_height;
    	if (side == 1)
        	color = game->textures[EAST][tex_y * 128 + tex_x];
    	else if (side == 2)
        	color = game->textures[WEST][tex_y * 128 + tex_x];
    	else if (side == 3)
        	color = game->textures[SOUTH][tex_y * 128 + tex_x];
    	else
        	color = game->textures[NORTH][tex_y * 128 + tex_x];
    	put_pixel(i, start_y, color, game);
    	start_y++;
	}
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaaa
	float	ray_x = player->x;
	float	ray_y = player->y;
	hit = 0;
	while (!touch_bola(ray_x, ray_y, game->bola) && (ray_x <= game->mapinfo.height * 64 && ray_x >= 0) && (ray_y <= game->mapinfo.width * 64 && ray_y >= 0))
	{
		// printf("%i,%i\n", game->mapinfo.height * 64, game->mapinfo.width * 64);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (touch_bola(ray_x, ray_y, game->bola))
		hit = 1;

	dist = distance(ray_x - player->x, ray_y - player->y);
	height = (FIRE / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	if (hit == 1)
	{
		while (start_y < end)
		{
			put_pixel(i, start_y, 100, game);
			start_y++;
		}
	}
}

void	draw_background(t_game *game)
{
	int		x;
	int		y;
	int		*floor;
	int		*ceiling;

	y = 0;
	floor = game->texinfo.floor;
	ceiling = game->texinfo.ceiling;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, (ceiling[0] << 16) | (ceiling[1] << 8) | ceiling[2], game);
			put_pixel(x, (y + HEIGHT / 2), (floor[0] << 16) | (floor[1] << 8) | floor[2], game);
			x++;
		}
		y++;
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;

	player = &game->player;
	move_player(game, player);
	move_bolas(game);
	clear_image(game);
	draw_background(game);
	// draw_square(player->x /*/ 2*/, player->y /*/ 2*/, 10, game);
	// draw_map(game);
	// draw_bolas(game, game->bola);

	float	fraction = PI / 3 / WIDTH;
	float	start_x = player->angle - PI / 6;
	int		i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (1);
}
