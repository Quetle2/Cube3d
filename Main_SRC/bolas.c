/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bolas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:25:36 by marada            #+#    #+#             */
/*   Updated: 2026/01/27 16:28:38 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

int		check_colisao(t_game *game, t_bola *bola)
{
	if (ft_strchr("1A", game->map[(int)((bola->y - (bola->sin_angle * SPEED)) / 64)] 
	[(int)((bola->x - (bola->cos_angle * SPEED)) / 64)]) != NULL
	|| ft_strchr("1A", game->map[(int)((bola->y - (bola->sin_angle * SPEED)) / 64)] 
	[(int)((bola->x + 20 - (bola->cos_angle * SPEED)) / 64)]) != NULL 
	|| ft_strchr("1A", game->map[(int)((bola->y + 20 - (bola->sin_angle * SPEED)) / 64)] 
	[(int)((bola->x - (bola->cos_angle * SPEED)) / 64)]) != NULL 
	|| ft_strchr("1A", game->map[(int)((bola->y + 20 - (bola->sin_angle * SPEED)) / 64)] 
	[(int)((bola->x + 20 - (bola->cos_angle * SPEED)) / 64)]) != NULL)
		return (1);
	return (0);
}

void	delete_bolas(t_list **bolas)
{
	free((*bolas)->content);
	while ((*bolas)->next)
	{
		(*bolas)->content = (*bolas)->next->content;
		*bolas = (*bolas)->next;
	}
	(*bolas)->content = NULL;
	// free(*bolas);
	// *bolas = NULL;
}

void	move_bolas(t_game  *game)
{
	t_list	*bolas;
	t_bola	*bola;
	
	bolas = game->bola;
	while (game->bola)
	{
		bola = game->bola->content;
		if (bola == NULL)
		{
			game->bola = game->bola->next;
			continue;
		}
		if (check_colisao(game, bola))
		{
			delete_bolas(&game->bola);
			continue;
		}
		bola->x -= bola->cos_angle * SPEED;
		bola->y -= bola->sin_angle  * SPEED;
		game->bola = game->bola->next;
	}
	game->bola = bolas;
}
