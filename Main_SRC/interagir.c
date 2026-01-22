/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interagir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:40:09 by marada            #+#    #+#             */
/*   Updated: 2026/01/22 19:13:29 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

void	interagir(t_game *game, t_player *player)
{
	if (ft_strchr("A", game->map[(int)((player->y - (player->sin_angle * SPEED)) / 64)] 
		[(int)((player->x - (player->cos_angle * SPEED)) / 64)]) != NULL)
	{
		printf("ola1\n");
		game->map[(int)((player->y - (player->sin_angle * SPEED)) / 64)] 
		[(int)((player->x - (player->cos_angle * SPEED)) / 64)] = 'F';
		printf("ola2\n");
	}
}