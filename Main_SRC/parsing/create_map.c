/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:17:56 by marada            #+#    #+#             */
/*   Updated: 2026/03/16 17:58:11 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

int	get_map_info(t_game *game, char **file, int i)
{
	game->mapinfo.height = count_map_lines(game, file, i);
	game->map = malloc(sizeof(char *) * (game->mapinfo.height + 1));
	if (!game->map)
		return (msg_err(NULL, "Opa essas memorias e tal", 1));
	if (fill_map_tab(&game->mapinfo, game->map, i) == 1)
		return (1);
	return (0);
}

void	change_space_into_wall(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (game->map[x])
	{
		y = 0;
		while (!is_a_white_space(game->map[x][y]))
			y++;
		while (game->map[x][y])
		{
			if (game->map[x][y] == ' '
				&& y != game->map[x][ft_strlen(game->map[x]) - 1])
				game->map[x][y] = '1';
			y++;
		}
		x++;
	}
}

int	create_map(t_game *game, char **file, int i)
{
	if (get_map_info(game, file, i) == 1)
		return (1);
	change_space_into_wall(game);
	return (0);
}
