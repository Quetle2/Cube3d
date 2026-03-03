/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:26:18 by marada            #+#    #+#             */
/*   Updated: 2026/03/03 17:00:38 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

void	move_left(char **map, t_player *player, float cos, float sin)
{
	if (ft_strchr("1A", map[(int)((player->y + 10
					+ (cos * SPEED * player->gear)) / 64)]
		[(int)((player->x - (sin * SPEED * player->gear)) / 64)]) != NULL)
		move_left_helper1(map, player, cos, sin);
	else if (ft_strchr("1A", map[(int)((player->y + 10
					+ (cos * SPEED * player->gear)) / 64)]
		[(int)((player->x + 10 - (sin * SPEED * player->gear)) / 64)]) != NULL)
		move_left_helper2(map, player, cos, sin);
	else if (ft_strchr("1A", map[(int)((player->y
					+ (cos * SPEED * player->gear)) / 64)]
		[(int)((player->x - (sin * SPEED * player->gear)) / 64)]) != NULL)
		move_left_helper3(map, player, cos, sin);
	else if (ft_strchr("1A", map[(int)((player->y + 10
					+ (cos * SPEED * player->gear)) / 64)]
		[(int)((player->x + 10 - (sin * SPEED * player->gear)) / 64)]) != NULL)
		move_left_helper4(map, player, cos, sin);
}

void	move_right(char **map, t_player *player, float cos, float sin)
{
	if (ft_strchr("1A", map[(int)((player->y + 10
					- (cos * SPEED * player->gear)) / 64)]
		[(int)((player->x + (sin * SPEED * player->gear)) / 64)]) != NULL)
		move_right_helper1(map, player, cos, sin);
	else if (ft_strchr("1A", map[(int)((player->y + 10
					- (cos * SPEED * player->gear)) / 64)]
		[(int)((player->x + 10 + (sin * SPEED * player->gear)) / 64)]) != NULL)
		move_right_helper2(map, player, cos, sin);
	else if (ft_strchr("1A", map[(int)((player->y
					- (cos * SPEED * player->gear)) / 64)]
		[(int)((player->x + (sin * SPEED * player->gear)) / 64)]) != NULL)
		move_right_helper3(map, player, cos, sin);
	else if (ft_strchr("1A", map[(int)((player->y + 10
					- (cos * SPEED * player->gear)) / 64)]
		[(int)((player->x + 10 + (sin * SPEED * player->gear)) / 64)]) != NULL)
		move_right_helper4(map, player, cos, sin);
}

void	move_down(char **map, t_player *player, float cos, float sin)
{
	if (ft_strchr("1A", map[(int)((player->y + 10
					+ (sin * SPEED * player->gear)) / 64)]
		[(int)((player->x + (cos * SPEED * player->gear)) / 64)]) != NULL)
		move_down_helper1(map, player, cos, sin);
	else if (ft_strchr("1A", map[(int)((player->y + 10
					+ (sin * SPEED * player->gear)) / 64)]
		[(int)((player->x + 10 + (cos * SPEED * player->gear)) / 64)]) != NULL)
		move_down_helper2(map, player, cos, sin);
	else if (ft_strchr("1A", map[(int)((player->y
					+ (sin * SPEED * player->gear)) / 64)]
		[(int)((player->x + (cos * SPEED * player->gear)) / 64)]) != NULL)
		move_down_helper3(map, player, cos, sin);
	else if (ft_strchr("1A", map[(int)((player->y + 10
					+ (sin * SPEED * player->gear)) / 64)]
		[(int)((player->x + 10 + (cos * SPEED * player->gear)) / 64)]) != NULL)
		move_down_helper4(map, player, cos, sin);
}

void	move_up(char **map, t_player *player, float cos, float sin)
{
	if (ft_strchr("1A", map[(int)((player->y + 10
					- (sin * SPEED * player->gear)) / 64)]
		[(int)((player->x - (cos * SPEED * player->gear)) / 64)]) != NULL)
		move_up_helper1(map, player, cos, sin);
	else if (ft_strchr("1A", map[(int)((player->y + 10
					- (sin * SPEED * player->gear)) / 64)]
		[(int)((player->x + 10 - (cos * SPEED * player->gear)) / 64)]) != NULL)
		move_up_helper2(map, player, cos, sin);
	else if (ft_strchr("1A", map[(int)((player->y
					- (sin * SPEED * player->gear)) / 64)]
		[(int)((player->x - (cos * SPEED * player->gear)) / 64)]) != NULL)
		move_up_helper3(map, player, cos, sin);
	else if (ft_strchr("1A", map[(int)((player->y + 10
					- (sin * SPEED * player->gear)) / 64)]
		[(int)((player->x + 10 - (cos * SPEED * player->gear)) / 64)]) != NULL)
		move_up_helper4(map, player, cos, sin);
}

void	move_player(t_game *game, t_player *player)
{
	float	angle_speed;

	angle_speed = 0.1;
	player->cos_angle = cos(player->angle);
	player->sin_angle = sin(player->angle);
	if (player->left_rotate == 1)
		player->angle -= angle_speed * player->gear;
	if (player->right_rotate == 1)
		player->angle += angle_speed * player->gear;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	pabaixo_helper(game, player);
	padireita_helper(game, player);
	pacima_helper(game, player);
	paesquerda_helper(game, player);
}
