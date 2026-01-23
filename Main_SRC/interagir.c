/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interagir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:40:09 by marada            #+#    #+#             */
/*   Updated: 2026/01/23 17:20:25 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

void	checka_porta(t_game *game,t_player *player, int size_y, int size_x)
{
	if (ft_strchr("A", game->map[(int)((player->y + size_y - (player->sin_angle * SPEED)) / 64)] 
		[(int)((player->x + size_x - (player->cos_angle * SPEED)) / 64)]) != NULL)
	{
		game->map[(int)((player->y + size_y - (player->sin_angle * SPEED)) / 64)] 
		[(int)((player->x + size_x - (player->cos_angle * SPEED)) / 64)] = 'F';
	}
	else if (ft_strchr("F", game->map[(int)((player->y + size_y - (player->sin_angle * SPEED)) / 64)] 
		[(int)((player->x + size_x - (player->cos_angle * SPEED)) / 64)]) != NULL)
	{
		game->map[(int)((player->y + size_y - (player->sin_angle * SPEED)) / 64)] 
		[(int)((player->x + size_x - (player->cos_angle * SPEED)) / 64)] = 'A';
	}
}

void	interagir(t_game *game, t_player *player)
{
	int	size_x;
	int	size_y;

	size_x = 0;
	size_y = 0;
	if (SPEED * player->sin_angle < 0)
		size_y = 10;
	if (SPEED * player->cos_angle < 0)
		size_x = 10;
	checka_porta(game, player, size_y, size_x);
}
