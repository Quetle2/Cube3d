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

	start_y = -wall_height / 2 + HEIGHT / 2;
	if (start_y < 0)
		start_y = 0;
	end = wall_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;

	// if (side == 0)
	// {
	// 	if ()
	// }
	// else
	// {

	// }
	while (start_y < end)
	{
		if (side == 1)
			put_pixel(i, start_y, 200, game);
		else if (side == 2)
			put_pixel(i, start_y, 100, game);
		else if (side == 3)
			put_pixel(i, start_y, 50, game);
		else if (side == 4)
			put_pixel(i, start_y, 150, game);
		start_y++;
	}
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaaa
	// ray_x = player->x;
	// ray_y = player->y;
	// while (!touch_bola(ray_x, ray_y, game->bola) && !touch(ray_x, ray_y, game))
	// {
	// 	// put_pixel(ray_x, ray_y, 0xFF0000, game);
	// 	// printf("x:%i\ny:%i\n", ray_x, ray_y);
	// 	ray_x -= cos_angle;
	// 	ray_y -= sin_angle;
	// }
	// if (touch(ray_x, ray_y, game))
	// {

	// 	wich = 1;
	// }
	// else
	// 	wich = 0;
	// // exit(1);
	// dist = distance(ray_x - player->x, ray_y - player->y);
	// if (wich == 1)
	// 	height = (BLOCK / dist) * (WIDTH / 2);
	// else
	// 	height = (FIRE / dist) * (WIDTH / 2);
	// start_y = (HEIGHT - height) / 2;
	// end = start_y + height;

	// while (start_y < end)
	// {
	// 	if (wich == 1)
	// 		put_pixel(i, start_y, 255, game);
	// 	else
	// 		put_pixel(i, start_y, 100, game);
	// 	start_y++;
	// }
}

// void	draw_line(t_player *player, t_game *game, float start_x, int x)
// {
// 	float	cos_angle;
// 	float	sin_angle;
// 	int		mapX;
// 	int		mapY;
// 	float	sideDistX;
// 	float	sideDistY;
// 	float	deltaDistX;
// 	float	deltaDistY;
// 	float	perpWallDist;
// 	int		stepX;
// 	int		stepY;
// 	int		hit;
// 	int		side;
// 	int		lineHeight;
// 	int		start_y;
// 	int		end;
// 	float	projPlane;

// 	cos_angle = cos(start_x);
// 	sin_angle = sin(start_x);

// 	mapX = (int)(player->x / BLOCK);
// 	mapY = (int)(player->y / BLOCK);

// 	deltaDistX = fabs(BLOCK / cos_angle);
// 	deltaDistY = fabs(BLOCK / sin_angle);

// 	if (cos_angle < 0)
// 	{
// 		stepX = -1;
// 		sideDistX = (player->x - mapX * BLOCK) / fabs(cos_angle);
// 	}
// 	else
// 	{
// 		stepX = 1;
// 		sideDistX = ((mapX + 1) * BLOCK - player->x) / fabs(cos_angle);
// 	}
// 	if (sin_angle < 0)
// 	{
// 		stepY = -1;
// 		sideDistY = (player->y - mapY * BLOCK) / fabs(sin_angle);
// 	}
// 	else
// 	{
// 		stepY = 1;
// 		sideDistY = ((mapY + 1) * BLOCK - player->y) / fabs(sin_angle);
// 	}
// 	hit = 0;
// 	while (!hit)
// 	{
// 		if (sideDistX < sideDistY)
// 		{
// 			sideDistX += deltaDistX;
// 			mapX += stepX;
// 			side = 0;
// 		}
// 		else
// 		{
// 			sideDistY += deltaDistY;
// 			mapY += stepY;
// 			side = 1;
// 		}
// 		if (game->map[mapY][mapX] == '1')
// 			hit = 1;
// 	}
// 	if (side == 0)
// 		dist = (mapX * BLOCK - player->x + (1 - stepX) * BLOCK / 2) / cos_angle;
// 	else
// 		dist = (mapY * BLOCK - player->y + (1 - stepY) * BLOCK / 2) / sin_angle;

// 	projPlane = WIDTH / (2 * tan(PI / 6));
// 	wall_height = (int)((BLOCK / dist) * projPlane);

// 	start_y = -wall_height / 2 + HEIGHT / 2;
// 	if (start_y < 0)
// 		start_y = 0;
// 	end = wall_height / 2 + HEIGHT / 2;
// 	if (end >= HEIGHT)
// 		end = HEIGHT - 1;

// 	while (start_y < end)
// 	{
// 		if (side == 1)
// 			put_pixel(x, start_y, 100, game);
// 		else
// 			put_pixel(x, start_y, 150, game);
// 		start_y++;
// 	}
// }

int	draw_loop(t_game *game)
{
	t_player	*player;

	player = &game->player;
	move_player(game, player);
	move_bolas(game);
	clear_image(game);
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
