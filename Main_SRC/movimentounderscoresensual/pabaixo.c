/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pabaixo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:58:29 by marada            #+#    #+#             */
/*   Updated: 2026/03/03 17:57:21 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

void	pabaixo_helper(t_game *game, t_player *player)
{
	if (player->key_down == 1
		&& (ft_strchr("1A", game->map[(int)((player->y
						- (player->sin_angle * SPEED * player->gear)) / 64)]
			[(int)((player->x - (player->cos_angle
						* SPEED * player->gear)) / 64)]) != NULL
		|| ft_strchr("1A", game->map[(int)((player->y
						- (player->sin_angle * SPEED * player->gear)) / 64)]
			[(int)((player->x + 10 - (player->cos_angle
						* SPEED * player->gear)) / 64)]) != NULL
		|| ft_strchr("1A", game->map[(int)((player->y
						+ 10 - (player->sin_angle
						* SPEED * player->gear)) / 64)]
			[(int)((player->x - (player->cos_angle
						* SPEED * player->gear)) / 64)]) != NULL
		|| ft_strchr("1A", game->map[(int)((player->y
						+ 10 - (player->sin_angle
						* SPEED * player->gear)) / 64)]
			[(int)((player->x + 10 - (player->cos_angle
						* SPEED * player->gear)) / 64)]) != NULL))
		move_down(game->map, player, player->cos_angle, player->sin_angle);
	else if (player->key_down == 1)
	{
		player->x -= player->cos_angle * SPEED * player->gear;
		player->y -= player->sin_angle * SPEED * player->gear;
	}
}

void	move_down_helper1(char **map, t_player *player, float cos, float sin)
{
	int	x_wall;
	int	y_wall;

	x_wall = (int)((player->x + (cos * SPEED * player->gear)) / 64)*64;
	y_wall = (int)((player->y + 10 + (sin * SPEED * player->gear)) / 64)*64;
	if (ft_strchr("1A", map[(int)((player->y + 10) / 64)]
		[(int)((player->x + (cos * SPEED * player->gear)) / 64)]) != NULL)
	{
		if (cos * SPEED * player->gear < 0)
			player->x -= (int)(player->x) - x_wall - BLOCK - 1;
	}
	if (ft_strchr("1A", map[(int)((player->y + 10
					+ (sin * SPEED * player->gear)) / 64)]
		[(int)((player->x) / 64)]) != NULL)
	{
		if (sin * SPEED * player->gear > 0)
			player->y += y_wall - (int)(player->y + 10) - 1;
	}
}

void	move_down_helper2(char **map, t_player *player, float cos, float sin)
{
	int	x_wall;
	int	y_wall;

	x_wall = (int)((player->x + 10 + (cos * SPEED * player->gear)) / 64)*64;
	y_wall = (int)((player->y + 10 + (sin * SPEED * player->gear)) / 64)*64;
	if (ft_strchr("1A", map[(int)((player->y + 10) / 64)]
		[(int)((player->x + 10 + (cos * SPEED * player->gear)) / 64)]) != NULL)
	{
		if (cos * SPEED * player->gear > 0)
			player->x += x_wall - (int)(player->x + 10) - 1;
	}
	if (ft_strchr("1A", map[(int)((player->y + 10
					+ (sin * SPEED * player->gear)) / 64)]
		[(int)((player->x) / 64)]) != NULL)
	{
		if (sin * SPEED * player->gear > 0)
			player->y += y_wall - (int)(player->y + 10) - 1;
	}
}

void	move_down_helper3(char **map, t_player *player, float cos, float sin)
{
	int	x_wall;
	int	y_wall;

	x_wall = (int)((player->x + (cos * SPEED * player->gear)) / 64)*64;
	y_wall = (int)((player->y + (sin * SPEED * player->gear)) / 64)*64;
	if (ft_strchr("1A", map[(int)((player->y) / 64)]
		[(int)((player->x + (cos * SPEED * player->gear)) / 64)]) != NULL)
	{
		if (cos * SPEED * player->gear < 0)
			player->x -= (int)(player->x) - x_wall - BLOCK - 1;
	}
	if (ft_strchr("1A", map[(int)((player->y
					+ (sin * SPEED * player->gear)) / 64)]
		[(int)((player->x) / 64)]) != NULL)
	{
		if (sin * SPEED * player->gear < 0)
			player->y -= (int)(player->y) - y_wall - BLOCK - 1;
	}
}

void	move_down_helper4(char **map, t_player *player, float cos, float sin)
{
	int	x_wall;
	int	y_wall;

	x_wall = (int)((player->x + 10 + (cos * SPEED * player->gear)) / 64)*64;
	y_wall = (int)((player->y + (sin * SPEED * player->gear)) / 64)*64;
	if (ft_strchr("1A", map[(int)((player->y) / 64)]
		[(int)((player->x + 10 + (cos * SPEED * player->gear)) / 64)]) != NULL)
	{
		if (cos * SPEED * player->gear > 0)
			player->x += x_wall - (int)(player->x + 10) - 1;
	}
	if (ft_strchr("1A", map[(int)((player->y
					+ (sin * SPEED * player->gear)) / 64)]
		[(int)((player->x + 10) / 64)]) != NULL)
	{
		if (sin * SPEED * player->gear < 0)
			player->y -= (int)(player->y) - y_wall - BLOCK - 1;
	}
}
