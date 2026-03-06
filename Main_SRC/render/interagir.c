/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interagir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:40:09 by marada            #+#    #+#             */
/*   Updated: 2026/03/06 01:07:03 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

void	checka_porta(t_game *game, t_player *player, int size_y, int size_x)
{
	if (ft_strchr("A", game->map[(int)((player->y + size_y
					+ (player->sin_angle * SPEED)) / 64)]
		[(int)((player->x + size_x
				+ (player->cos_angle * SPEED)) / 64)]) != NULL)
	{
		game->map[(int)((player->y
					+ size_y + (player->sin_angle * SPEED)) / 64)]
		[(int)((player->x + size_x + (player->cos_angle * SPEED)) / 64)] = 'F';
	}
	else if (ft_strchr("F", game->map[(int)((player->y
					+ size_y + (player->sin_angle * SPEED)) / 64)]
		[(int)((player->x + size_x
				+ (player->cos_angle * SPEED)) / 64)]) != NULL)
	{
		game->map[(int)((player->y
					+ size_y + (player->sin_angle * SPEED)) / 64)]
		[(int)((player->x + size_x + (player->cos_angle * SPEED)) / 64)] = 'A';
	}
}

void	interagir(t_game *game, t_player *player)
{
	int	size_x;
	int	size_y;

	size_x = 0;
	size_y = 0;
	if (SPEED * player->sin_angle > 0)
		size_y = 10;
	if (SPEED * player->cos_angle > 0)
		size_x = 10;
	checka_porta(game, player, size_y, size_x);
}

void	bola_de_fogo(t_game *game, t_player *player)
{
	int		size_x;
	int		size_y;
	t_bola	*bula;

	size_x = 0;
	size_y = 0;
	if (SPEED * player->sin_angle < 0)
		size_y = 10 * player->sin_angle;
	if (SPEED * player->cos_angle < 0)
		size_x = 10 * player->cos_angle;
	bula = malloc(sizeof(t_bola));
	bula->x = player->x - (player->cos_angle * SPEED) + size_x;
	bula->y = player->y - (player->sin_angle * SPEED) + size_y;
	bula->cos_angle = player->cos_angle;
	bula->sin_angle = player->sin_angle;
	ft_lstadd_back(&game->bola, ft_lstnew(bula));
}

void	gear_shift(t_player *player)
{
	if (player->gear == 1)
		player->gear += 4;
	else if (player->gear < 15)
		player->gear += 5;
	else
		player->gear = 1;
}
