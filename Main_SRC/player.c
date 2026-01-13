/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:26:18 by marada            #+#    #+#             */
/*   Updated: 2026/01/13 19:07:15 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

void init_player(t_player *player)
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
	if(keycode == W)
		player->key_up = 1;
	if(keycode == S)
		player->key_down = 1;
	if(keycode == A)
		player->key_left = 1;
	if(keycode == D)
		player->key_right = 1;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if(keycode == W)
		player->key_up = 0;
	if(keycode == S)
		player->key_down = 0;
	if(keycode == A)
		player->key_left = 0;
	if(keycode == D)
		player->key_right = 0;
	return (0);
}

void	move_player(t_player *player)
{
	int	spped = 5;
}