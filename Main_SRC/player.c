/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:26:18 by marada            #+#    #+#             */
/*   Updated: 2026/01/20 15:54:29 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;

	player->key_up = 0;
	player->key_down = 0;
	player->key_left = 0;
	player->key_right = 0;
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = 1;
	if (keycode == S)
		player->key_down = 1;
	if (keycode == A)
		player->key_left = 1;
	if (keycode == D)
		player->key_right = 1;
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
	return (0);
}

void	move_down(char **map, t_player *player, int speed)
{
	int	x_wall;
	int y_wall;

	if (map[(int)((player->y + 10 + speed) / 64)]
		[(int)(player->x / 64)] == '1')
	{
		x_wall = (int)(player->x / 64) * 64;
		y_wall = (int)((player->y + 10 + speed) / 64) * 64;
		player->y += y_wall - (int)(player->y + 10) - 1;
	}
	else if(map[(int)((player->y + 10 + speed) / 64)]
		[(int)((player->x + 10) / 64)] == '1')
	{
		x_wall = (int)(player->x + 10 / 64) * 64;
		y_wall = (int)((player->y + 10 + speed) / 64) * 64;
		player->y += y_wall - (int)(player->y + 10) - 1;
	}
}

void	move_up(char **map, t_player *player, int speed)
{
	int	x_wall;
	int y_wall;
	printf("A%f : %f B%i\n", player->y, player->x, (int)((player->y - speed) / 64) * 64);
	if (map[(int)((player->y - speed) / 64)]
		[(int)(player->x / 64)] == '1')
	{
		x_wall = (int)(player->x / 64) * 64;
		y_wall = (int)((player->y - speed) / 64) * 64;
		player->y -= (int)(player->y) - y_wall - BLOCK - 1;
	}
	else if(map[(int)((player->y - speed) / 64)]
		[(int)(player->x + 10 / 64)] == '1')
	{
		x_wall = (int)(player->x + 10 / 64) * 64;
		y_wall = (int)((player->y - speed) / 64) * 64;
		player->y -= (int)(player->y) - y_wall - BLOCK - 1;
	}
}

void	move_left(char **map, t_player *player, int speed)
{
	int	x_wall;
	int y_wall;

	if (map[(int)((player->y) / 64)]
		[(int)(player->x - speed / 64)] == '1')
	{
		x_wall = (int)(player->x - speed / 64) * 64;
		y_wall = (int)((player->y) / 64) * 64;
		player->x -= (int)(player->x) - x_wall - BLOCK - 1;
	}
	else if(map[(int)((player->y + 10) / 64)]
		[(int)((player->x - speed) / 64)] == '1')
	{
		x_wall = (int)((player->x - speed) / 64) * 64;
		y_wall = (int)((player->y + 10) / 64) * 64;
		player->x -= (int)(player->x) - x_wall - BLOCK - 1;
	}
}

void	move_right(char **map, t_player *player, int speed)
{
	int	x_wall;
	int y_wall;

	if (map[(int)((player->y) / 64)]
		[(int)(player->x + 10 + speed/ 64)] == '1')
	{
		x_wall = (int)(player->x + 10 + speed / 64) * 64;
		y_wall = (int)((player->y) / 64) * 64;
		player->x += x_wall - (int)(player->x + 10) - 1;
	}
	else if(map[(int)((player->y + 10 + speed) / 64)]
		[(int)((player->x + 10) / 64)] == '1')
	{
		x_wall = (int)(player->x + 10 + speed / 64) * 64;
		y_wall = (int)((player->y + 10) / 64) * 64;
		player->x += x_wall - (int)(player->x + 10) - 1;
	}
}

void	move_player(t_game *game, t_player *player)
{
	int	speed;

	speed = 5;
	if (player->key_left == 1 
		&& (game->map[(int)(player->y / 64)] 
		[(int)((player->x - speed) / 64)] == '1'
		|| game->map[(int)((player->y + 10) / 64)] 
		[(int)((player->x - speed) / 64)] == '1'))
		move_left(game->map, player, speed);
	else if (player->key_left == 1)
		player->x -= speed;
	if (player->key_up == 1
		&& (game->map[(int)((player->y - speed) / 64)]
		[(int)(player->x / 64)] == '1'
		|| game->map[(int)((player->y - speed) / 64)]
		[(int)((player->x + 10) / 64)] == '1'))
		move_up(game->map, player, speed);
	else if (player->key_up == 1)
		player->y -= speed;
	if (player->key_down == 1
		&& (game->map[(int)((player->y + 10 + speed) / 64)]
		[(int)(player->x / 64)] == '1'
		|| game->map[(int)((player->y + 10 + speed) / 64)]
		[(int)((player->x + 10) / 64)] == '1'))
		move_down(game->map, player, speed);
	else if(player->key_down == 1)
		player->y += speed;
	if (player->key_right == 1
		&& (game->map[(int)(player->y / 64)]
		[(int)((player->x + 11) / 64)] == '1'
		|| game->map[(int)((player->y + 10) / 64.00)]
		[(int)((player->x + 11) / 64)] == '1'))
		move_right(game->map, player, speed);
	else if(player->key_right == 1)
		player->x += speed;
}
