/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:26:18 by marada            #+#    #+#             */
/*   Updated: 2026/02/07 21:11:00 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->angle = PI / 2;

	player->key_up = 0;
	player->key_down = 0;
	player->key_left = 0;
	player->key_right = 0;

	player->left_rotate = 0;
	player->right_rotate = 0;
}

int	key_press(int keycode, t_game *game)
{
	t_player *player;

	player = &game->player;
	if (keycode == W)
		player->key_up = 1;
	if (keycode == S)
		player->key_down = 1;
	if (keycode == A)
		player->key_left = 1;
	if (keycode == D)
		player->key_right = 1;
	if (keycode == LEFT)
		player->left_rotate = 1;
	if (keycode == RIGHT)
		player->right_rotate = 1;
	if (keycode == F)
		interagir(game, player);
	if (keycode == Q)
		BOLA_DE_FOGO(game, player);
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = 0;
	if (keycode == S)
		player->key_down = 0;
	if (keycode == A)
		player->key_left = 0;
	if (keycode == D)
		player->key_right = 0;
	if (keycode == LEFT)
		player->left_rotate = 0;
	if (keycode == RIGHT)
		player->right_rotate = 0;
	return (0);
}

void	move_left(char **map, t_player *player, float cos, float sin)
{
	int	x_wall;
	int y_wall;

	if (ft_strchr("1A", map[(int)((player->y + 10 + (cos * SPEED)) / 64)] 
		[(int)((player->x - (sin * SPEED)) / 64)]) != NULL)
	{
		x_wall = (int)((player->x - (sin * SPEED)) / 64) * 64;
		y_wall = (int)((player->y + 10 + (cos * SPEED)) / 64) * 64;
		if(ft_strchr("1A", map[(int)((player->y + 10) / 64)] 
		[(int)((player->x - (sin * SPEED)) / 64)]) != NULL)
		{
			if (sin * SPEED > 0)
				player->x -= (int)(player->x) - x_wall - BLOCK - 1;
		}
		if (ft_strchr("1A", map[(int)((player->y + 10 + (cos * SPEED)) / 64)] 
		[(int)((player->x) / 64)]) != NULL)
		{
			if (cos * SPEED > 0)
				player->y += y_wall - (int)(player->y + 10) - 1;
		}
	}
	else if(ft_strchr("1A", map[(int)((player->y + 10 + (cos * SPEED)) / 64)] 
		[(int)((player->x + 10 - (sin * SPEED)) / 64)]) != NULL)
	{
		x_wall = (int)((player->x + 10 - (sin * SPEED)) / 64) * 64;
		y_wall = (int)((player->y + 10 + (cos * SPEED)) / 64) * 64;
		if(ft_strchr("1A", map[(int)((player->y + 10) / 64)]
		[(int)((player->x + 10 - (sin * SPEED)) / 64)]) != NULL)
		{
			if (sin * SPEED < 0)
				player->x += x_wall - (int)(player->x + 10) - 1;
		}
		if (ft_strchr("1A", map[(int)((player->y + 10 + (cos * SPEED)) / 64)] 
		[(int)((player->x) / 64)]) != NULL)
		{
			if (cos * SPEED > 0)
				player->y += y_wall - (int)(player->y + 10) - 1;
		}
	}
	else if(ft_strchr("1A", map[(int)((player->y + (cos * SPEED)) / 64)] 
		[(int)((player->x - (sin * SPEED)) / 64)]) != NULL)
	{
		x_wall = (int)((player->x - (sin * SPEED)) / 64) * 64;
		y_wall = (int)((player->y + (cos * SPEED)) / 64) * 64;
		if(ft_strchr("1A", map[(int)((player->y) / 64)]
		[(int)((player->x - (sin * SPEED)) / 64)]) != NULL)
		{
			if (sin * SPEED > 0)
				player->x -= (int)(player->x) - x_wall - BLOCK - 1;
		}
		if (ft_strchr("1A", map[(int)((player->y + (cos * SPEED)) / 64)] 
		[(int)((player->x) / 64)]) != NULL)
		{
			if (cos * SPEED < 0)
				player->y -= (int)(player->y) - y_wall - BLOCK - 1;
		}
	}
	else if(ft_strchr("1A", map[(int)((player->y + 10 + (cos * SPEED)) / 64)] 
		[(int)((player->x + 10 - (sin * SPEED)) / 64)]) != NULL)
	{
		x_wall = (int)((player->x + 10 - (sin * SPEED)) / 64) * 64;
		y_wall = (int)((player->y + (cos * SPEED)) / 64) * 64;
		if(ft_strchr("1A", map[(int)((player->y) / 64)]
		[(int)((player->x + 10 - (sin * SPEED)) / 64)]) != NULL)
		{
			if (sin * SPEED < 0)
				player->x += x_wall - (int)(player->x + 10) - 1;
		}
		if (ft_strchr("1A", map[(int)((player->y + (cos * SPEED)) / 64)] 
		[(int)((player->x + 10) / 64)]) != NULL)
		{
			if (cos * SPEED < 0)
				player->y -= (int)(player->y) - y_wall - BLOCK - 1;
		}
	}
}

void	move_right(char **map, t_player *player, float cos, float sin)
{
	int	x_wall;
	int y_wall;

	if (ft_strchr("1A", map[(int)((player->y + 10 - (cos * SPEED)) / 64)] 
		[(int)((player->x + (sin * SPEED)) / 64)]) != NULL)
	{
		x_wall = (int)((player->x + (sin * SPEED)) / 64) * 64;
		y_wall = (int)((player->y + 10 - (cos * SPEED)) / 64) * 64;
		if(ft_strchr("1A", map[(int)((player->y + 10) / 64)] 
		[(int)((player->x + (sin * SPEED)) / 64)]) != NULL)
		{
			if (sin * SPEED < 0)
				player->x -= (int)(player->x) - x_wall - BLOCK - 1;
		}
		if (ft_strchr("1A", map[(int)((player->y + 10 - (cos * SPEED)) / 64)] 
		[(int)((player->x) / 64)]) != NULL)
		{
			if (cos * SPEED < 0)
				player->y += y_wall - (int)(player->y + 10) - 1;
		}
	}
	else if(ft_strchr("1A", map[(int)((player->y + 10 - (cos * SPEED)) / 64)] 
		[(int)((player->x + 10 + (sin * SPEED)) / 64)]) != NULL)
	{
		x_wall = (int)((player->x + 10 + (sin * SPEED)) / 64) * 64;
		y_wall = (int)((player->y + 10 - (cos * SPEED)) / 64) * 64;
		if(ft_strchr("1A", map[(int)((player->y + 10) / 64)]
		[(int)((player->x + 10 + (sin * SPEED)) / 64)]) != NULL)
		{
			if (sin * SPEED > 0)
				player->x += x_wall - (int)(player->x + 10) - 1;
		}
		if (ft_strchr("1A", map[(int)((player->y + 10 - (cos * SPEED)) / 64)] 
		[(int)((player->x) / 64)]) != NULL)
		{
			if (cos * SPEED < 0)
				player->y += y_wall - (int)(player->y + 10) - 1;
		}
	}
	else if(ft_strchr("1A", map[(int)((player->y - (cos * SPEED)) / 64)] 
		[(int)((player->x + (sin * SPEED)) / 64)]) != NULL)
	{
		x_wall = (int)((player->x + (sin * SPEED)) / 64) * 64;
		y_wall = (int)((player->y - (cos * SPEED)) / 64) * 64;
		if(ft_strchr("1A", map[(int)((player->y) / 64)]
		[(int)((player->x + (sin * SPEED)) / 64)]) != NULL)
		{
			if (sin * SPEED < 0)
				player->x -= (int)(player->x) - x_wall - BLOCK - 1;
		}
		if (ft_strchr("1A", map[(int)((player->y - (cos * SPEED)) / 64)] 
		[(int)((player->x) / 64)]) != NULL)
		{
			if (cos * SPEED > 0)
				player->y -= (int)(player->y) - y_wall - BLOCK - 1;
		}
	}
	else if(ft_strchr("1A", map[(int)((player->y + 10 - (cos * SPEED)) / 64)] 
		[(int)((player->x + 10 + (sin * SPEED)) / 64)]) != NULL)
	{
		x_wall = (int)((player->x + 10 + (sin * SPEED)) / 64) * 64;
		y_wall = (int)((player->y - (cos * SPEED)) / 64) * 64;
		if(ft_strchr("1A", map[(int)((player->y) / 64)]
		[(int)((player->x + 10 + (sin * SPEED)) / 64)]) != NULL)
		{
			if (sin * SPEED > 0)
				player->x += x_wall - (int)(player->x + 10) - 1;
		}
		if (ft_strchr("1A", map[(int)((player->y - (cos * SPEED)) / 64)] 
		[(int)((player->x + 10) / 64)]) != NULL)
		{
			if (cos * SPEED > 0)
				player->y -= (int)(player->y) - y_wall - BLOCK - 1;
		}
	}
}

void	move_down(char **map, t_player *player, float cos, float sin)
{
	int	x_wall;
	int y_wall;

	if (ft_strchr("1A", map[(int)((player->y + 10 + (sin * SPEED)) / 64)] 
		[(int)((player->x + (cos * SPEED)) / 64)]) != NULL)
	{
		x_wall = (int)((player->x + (cos * SPEED)) / 64) * 64;
		y_wall = (int)((player->y + 10 + (sin * SPEED)) / 64) * 64;
		if(ft_strchr("1A", map[(int)((player->y + 10) / 64)] 
		[(int)((player->x + (cos * SPEED)) / 64)]) != NULL)
		{
			if (cos * SPEED < 0)
				player->x -= (int)(player->x) - x_wall - BLOCK - 1;
		}
		if (ft_strchr("1A", map[(int)((player->y + 10 + (sin * SPEED)) / 64)] 
		[(int)((player->x) / 64)]) != NULL)
		{
			if (sin * SPEED > 0)
				player->y += y_wall - (int)(player->y + 10) - 1;
		}
	}
	else if(ft_strchr("1A", map[(int)((player->y + 10 + (sin * SPEED)) / 64)] 
		[(int)((player->x + 10 + (cos * SPEED)) / 64)]) != NULL)
	{
		x_wall = (int)((player->x + 10 + (cos * SPEED)) / 64) * 64;
		y_wall = (int)((player->y + 10 + (sin * SPEED)) / 64) * 64;
		if(ft_strchr("1A", map[(int)((player->y + 10) / 64)]
		[(int)((player->x + 10 + (cos * SPEED)) / 64)]) != NULL)
		{
			if (cos * SPEED > 0)
				player->x += x_wall - (int)(player->x + 10) - 1;
		}
		if (ft_strchr("1A", map[(int)((player->y + 10 + (sin * SPEED)) / 64)] 
		[(int)((player->x) / 64)]) != NULL)
		{
			if (sin * SPEED > 0)
				player->y += y_wall - (int)(player->y + 10) - 1;
		}
	}
	else if(ft_strchr("1A", map[(int)((player->y + (sin * SPEED)) / 64)] 
		[(int)((player->x + (cos * SPEED)) / 64)]) != NULL)
	{
		x_wall = (int)((player->x + (cos * SPEED)) / 64) * 64;
		y_wall = (int)((player->y + (sin * SPEED)) / 64) * 64;
		if(ft_strchr("1A", map[(int)((player->y) / 64)]
		[(int)((player->x + (cos * SPEED)) / 64)]) != NULL)
		{
			if (cos * SPEED < 0)
				player->x -= (int)(player->x) - x_wall - BLOCK - 1;
		}
		if (ft_strchr("1A", map[(int)((player->y + (sin * SPEED)) / 64)] 
		[(int)((player->x) / 64)]) != NULL)
		{
			if (sin * SPEED < 0)
				player->y -= (int)(player->y) - y_wall - BLOCK - 1;
		}
	}
	else if(ft_strchr("1A", map[(int)((player->y + 10 + (sin * SPEED)) / 64)] 
		[(int)((player->x + 10 + (cos * SPEED)) / 64)]) != NULL)
	{
		x_wall = (int)((player->x + 10 + (cos * SPEED)) / 64) * 64;
		y_wall = (int)((player->y + (sin * SPEED)) / 64) * 64;
		if(ft_strchr("1A", map[(int)((player->y) / 64)]
		[(int)((player->x + 10 + (cos * SPEED)) / 64)]) != NULL)
		{
			if (cos * SPEED > 0)
				player->x += x_wall - (int)(player->x + 10) - 1;
		}
		if (ft_strchr("1A", map[(int)((player->y + (sin * SPEED)) / 64)] 
		[(int)((player->x + 10) / 64)]) != NULL)
		{
			if (sin * SPEED < 0)
				player->y -= (int)(player->y) - y_wall - BLOCK - 1;
		}
	}
}

void	move_up(char **map, t_player *player, float cos, float sin)
{
	int	x_wall;
	int y_wall;

	if (ft_strchr("1A", map[(int)((player->y + 10 - (sin * SPEED)) / 64)] 
		[(int)((player->x - (cos * SPEED)) / 64)]) != NULL)
	{
		x_wall = (int)((player->x - (cos * SPEED)) / 64) * 64;
		y_wall = (int)((player->y + 10 - (sin * SPEED)) / 64) * 64;
		if(ft_strchr("1A", map[(int)((player->y + 10) / 64)] 
		[(int)((player->x - (cos * SPEED)) / 64)]) != NULL)
		{
			if (cos * SPEED > 0)
				player->x -= (int)(player->x) - x_wall - BLOCK - 1;
		}
		if (ft_strchr("1A", map[(int)((player->y + 10 - (sin * SPEED)) / 64)] 
		[(int)((player->x) / 64)]) != NULL)
		{
			if (sin * SPEED < 0)
				player->y += y_wall - (int)(player->y + 10) - 1;
		}
	}
	else if(ft_strchr("1A", map[(int)((player->y + 10 - (sin * SPEED)) / 64)] 
		[(int)((player->x + 10 - (cos * SPEED)) / 64)]) != NULL)
	{
		x_wall = (int)((player->x + 10 - (cos * SPEED)) / 64) * 64;
		y_wall = (int)((player->y + 10 - (sin * SPEED)) / 64) * 64;
		if(ft_strchr("1A", map[(int)((player->y + 10) / 64)]
		[(int)((player->x + 10 - (cos * SPEED)) / 64)]) != NULL)
		{
			if (cos * SPEED < 0)
				player->x += x_wall - (int)(player->x + 10) - 1;
		}
		if (ft_strchr("1A", map[(int)((player->y + 10 - (sin * SPEED)) / 64)] 
		[(int)((player->x) / 64)]) != NULL)
		{
			if (sin * SPEED < 0)
				player->y += y_wall - (int)(player->y + 10) - 1;
		}
	}
	else if(ft_strchr("1A", map[(int)((player->y - (sin * SPEED)) / 64)] 
		[(int)((player->x - (cos * SPEED)) / 64)]) != NULL)
	{
		x_wall = (int)((player->x - (cos * SPEED)) / 64) * 64;
		y_wall = (int)((player->y - (sin * SPEED)) / 64) * 64;
		if(ft_strchr("1A", map[(int)((player->y) / 64)]
		[(int)((player->x - (cos * SPEED)) / 64)]) != NULL)
		{
			if (cos * SPEED > 0)
				player->x -= (int)(player->x) - x_wall - BLOCK - 1;
		}
		if (ft_strchr("1A", map[(int)((player->y - (sin * SPEED)) / 64)] 
		[(int)((player->x) / 64)]) != NULL)
		{
			if (sin * SPEED > 0)
				player->y -= (int)(player->y) - y_wall - BLOCK - 1;
		}
	}
	else if(ft_strchr("1A", map[(int)((player->y + 10 - (sin * SPEED)) / 64)] 
		[(int)((player->x + 10 - (cos * SPEED)) / 64)]) != NULL)
	{
		x_wall = (int)((player->x + 10 - (cos * SPEED)) / 64) * 64;
		y_wall = (int)((player->y - (sin * SPEED)) / 64) * 64;
		if(ft_strchr("1A", map[(int)((player->y) / 64)]
		[(int)((player->x + 10 - (cos * SPEED)) / 64)]) != NULL)
		{
			if (cos * SPEED < 0)
				player->x += x_wall - (int)(player->x + 10) - 1;
		}
		if (ft_strchr("1A", map[(int)((player->y - (sin * SPEED)) / 64)] 
		[(int)((player->x + 10) / 64)]) != NULL)
		{
			if (sin * SPEED > 0)
				player->y -= (int)(player->y) - y_wall - BLOCK - 1;
		}
	}
}

void	move_player(t_game *game, t_player *player)
{
	float	angle_speed = 0.1;

	player->cos_angle = cos(player->angle);
	player->sin_angle = sin(player->angle);
	if (player->left_rotate == 1)
		player->angle -= angle_speed;
	if (player->right_rotate == 1)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
	 	player->angle = 2 * PI;

	if (player->key_up == 1
		&& (ft_strchr("1A", game->map[(int)((player->y - (player->sin_angle * SPEED)) / 64)] 
		[(int)((player->x - (player->cos_angle * SPEED)) / 64)]) != NULL
		|| ft_strchr("1A", game->map[(int)((player->y - (player->sin_angle * SPEED)) / 64)] 
		[(int)((player->x + 10 - (player->cos_angle * SPEED)) / 64)]) != NULL 
		|| ft_strchr("1A", game->map[(int)((player->y + 10 - (player->sin_angle * SPEED)) / 64)] 
		[(int)((player->x - (player->cos_angle * SPEED)) / 64)]) != NULL 
		|| ft_strchr("1A", game->map[(int)((player->y + 10 - (player->sin_angle * SPEED)) / 64)] 
		[(int)((player->x + 10 - (player->cos_angle * SPEED)) / 64)]) != NULL))
		move_up(game->map, player, player->cos_angle, player->sin_angle);
	else if (player->key_up == 1)
	{
		player->x -= player->cos_angle * SPEED;
		player->y -= player->sin_angle * SPEED;
	}
	if (player->key_left == 1 
		&& (ft_strchr("1A", game->map[(int)((player->y + (player->cos_angle * SPEED)) / 64)] 
		[(int)((player->x - (player->sin_angle * SPEED)) / 64)]) != NULL
		|| ft_strchr("1A", game->map[(int)((player->y + 10 + (player->cos_angle * SPEED)) / 64)] 
		[(int)((player->x - (player->sin_angle * SPEED)) / 64)]) != NULL 
		|| ft_strchr("1A", game->map[(int)((player->y + 10 + (player->cos_angle * SPEED)) / 64)] 
		[(int)((player->x + 10 - (player->sin_angle * SPEED)) / 64)]) != NULL 
		|| ft_strchr("1A", game->map[(int)((player->y + (player->cos_angle * SPEED)) / 64)] 
		[(int)((player->x + 10 - (player->sin_angle * SPEED)) / 64)]) != NULL))
		move_left(game->map, player, player->cos_angle, player->sin_angle);
	else if (player->key_left == 1)
	{
		player->x -= player->sin_angle * SPEED;
		player->y += player->cos_angle * SPEED;
	}
	if ((player->key_down == 1)
		&& (ft_strchr("1A", game->map[(int)((player->y + 10 + (player->sin_angle * SPEED)) / 64)] 
		[(int)((player->x + (player->cos_angle * SPEED)) / 64)]) != NULL
		|| ft_strchr("1A", game->map[(int)((player->y + 10 + (player->sin_angle * SPEED)) / 64)] 
		[(int)((player->x + 10 + (player->cos_angle * SPEED)) / 64)]) != NULL 
		|| ft_strchr("1A", game->map[(int)((player->y + (player->sin_angle * SPEED)) / 64)] 
		[(int)((player->x + (player->cos_angle * SPEED)) / 64)]) != NULL 
		|| ft_strchr("1A", game->map[(int)((player->y + (player->sin_angle * SPEED)) / 64)] 
		[(int)((player->x + 10 + (player->cos_angle * SPEED)) / 64)]) != NULL))
		move_down(game->map, player, player->cos_angle, player->sin_angle);
	else if(player->key_down == 1)
	{
		player->x += player->cos_angle * SPEED;
		player->y += player->sin_angle * SPEED;
	}
	if (player->key_right == 1
		&& (ft_strchr("1A", game->map[(int)((player->y - (player->cos_angle * SPEED)) / 64)] 
		[(int)((player->x + 10 + (player->sin_angle * SPEED)) / 64)]) != NULL
		|| ft_strchr("1A", game->map[(int)((player->y + 10 - (player->cos_angle * SPEED)) / 64)] 
		[(int)((player->x + 10 + (player->sin_angle * SPEED)) / 64)]) != NULL 
		|| ft_strchr("1A", game->map[(int)((player->y + 10 - (player->cos_angle * SPEED)) / 64)] 
		[(int)((player->x + (player->sin_angle * SPEED)) / 64)]) != NULL 
		|| ft_strchr("1A", game->map[(int)((player->y - (player->cos_angle * SPEED)) / 64)] 
		[(int)((player->x + (player->sin_angle * SPEED)) / 64)]) != NULL))
		move_right(game->map, player, player->cos_angle, player->sin_angle);
	else if(player->key_right == 1)
	{
		player->x += player->sin_angle * SPEED;
		player->y -= player->cos_angle * SPEED;
	}
}
