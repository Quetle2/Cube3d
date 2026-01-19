/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:26:18 by marada            #+#    #+#             */
/*   Updated: 2026/01/19 18:01:59 by marada           ###   ########.fr       */
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

void	move_down(char **map, t_player *player)
{
	
}

void	move_player(t_game *game, t_player *player)
{
	int	speed;

	speed = 5;
	printf("sitiox :%i sitioy:%i\n", (int)player->x, (int)player->y);
	if (player->key_left == 1 
		&& game->map[(int)(player->y / 64)] 
		[(int)((player->x - 2) / 64)] != '1'
		&& game->map[(int)((player->y + 10) / 64)] 
		[(int)((player->x - 2) / 64)] != '1')
		player->x -= speed;
	if (player->key_up == 1
		&& game->map[(int)((player->y - 2) / 64)]
		[(int)(player->x / 64)] != '1'
		&& game->map[(int)((player->y - 2) / 64)]
		[(int)((player->x + 10) / 64)] != '1')
		player->y -= speed;
	if (player->key_down == 1
		&& game->map[(int)((player->y + 11) / 64)]
		[(int)(player->x / 64)] != '1'
		&& game->map[(int)((player->y + 11) / 64)]
		[(int)((player->x + 10) / 64)] == '1')
		move_down(game->map, player);
	else
		player->y += speed;
	if (player->key_right == 1
		&& game->map[(int)(player->y / 64)]
		[(int)((player->x + 11) / 64)] != '1'
		&& game->map[(int)((player->y + 10) / 64.00)]
		[(int)((player->x + 11) / 64)] != '1')
		player->x += speed;
}
