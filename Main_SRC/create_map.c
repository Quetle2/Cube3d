/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:17:56 by marada            #+#    #+#             */
/*   Updated: 2026/03/05 00:40:37 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

int	get_map_info(t_game *game, char **file, int i)
{
	game->mapinfo.height = count_map_lines(game, file, i);
	game->map = malloc(sizeof(char *) * (game->mapinfo.height + 1));
	if (!game->map)
		return (err_msg(NULL, "Opa essas memorias e tal", 1));
	if (fill_map_tab(&game->mapinfo, game->map, i) == 1)
		return (1);
	return (0);
}

void	change_space_into_wall(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] == ' ' || game->map[i][j] == '\t'
		|| game->map[i][j] == '\r'
		|| game->map[i][j] == '\v' || game->map[i][j] == '\f')
			j++;
		while (game->map[i][j])
		{
			if (game->map[i][j] == ' '
				&& j != game->map[i][ft_strlen(game->map[i]) - 1])
				game->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	create_map(t_game *game, char **file, int i)
{
	if (get_map_info(game, file, i) == 1)
		return (1);
	change_space_into_wall(game);
	return (0);
}
