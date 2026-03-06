/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:32:13 by marada            #+#    #+#             */
/*   Updated: 2026/03/06 01:06:13 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

int	check_player_position(t_game *game, char **map_tab)
{
	int	i;
	int	j;

	i = 0;
	while (map_tab[i])
	{
		j = 0;
		while (map_tab[i][j])
		{
			if (ft_strchr("NSWE", map_tab[i][j]))
			{
				game->player.x = (double)j * BLOCK + BLOCK / 2 - 5;
				game->player.y = (double)i * BLOCK + BLOCK / 2 - 5;
				map_tab[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (check_position_is_valid(game, map_tab) == 1)
		return (err_msg(game->mapinfo.path, "ERROR: Position invalid.\n", 1));
	return (0);
}

int	check_map_elements(t_game *game, char **map_tab)
{
	int	i;
	int	j;

	i = 0;
	game->player.dir = '0';
	while (map_tab[i] != NULL)
	{
		j = 0;
		while (map_tab[i][j])
		{
			while (game->map[i][j] == ' ' || game->map[i][j] == '\t'
			|| (game->map[i][j] >= '\v' && game->map[i][j] <= '\r'))
				j++;
			if (!(ft_strchr("10NSWEAF", map_tab[i][j])))
				return (err_msg(game->mapinfo.path, "Invalid Map.\n", 1));
			if (ft_strchr("NSWE", map_tab[i][j]) && game->player.dir != '0')
				return (err_msg(game->mapinfo.path, "Invalid Map.\n", 1));
			if (ft_strchr("NSWE", map_tab[i][j]) && game->player.dir == '0')
				game->player.dir = map_tab[i][j];
			j++;
		}
		i++;
	}
	return (0);
}

int	check_top_or_bottom(char **map_tab, int i, int j)
{
	if (!map_tab || !map_tab[i] || !map_tab[i][j])
		return (1);
	while (map_tab[i][j] == ' ' || map_tab[i][j] == '\t'
	|| map_tab[i][j] == '\r' || map_tab[i][j] == '\v'
	|| map_tab[i][j] == '\f')
		j++;
	while (map_tab[i][j])
	{
		if (map_tab[i][j] != '1')
			return (1);
		j++;
	}
	return (0);
}

int	check_map_sides(t_mapinfo *map, char **map_tab)
{
	int		i;
	int		j;

	if (check_top_or_bottom(map_tab, 0, 0) == 1)
		return (1);
	i = 1;
	while (i < (map->height - 1))
	{
		j = ft_strlen(map_tab[i]) - 1;
		if (map_tab[i][j] != '1')
			return (1);
		i++;
	}
	if (check_top_or_bottom(map_tab, i, 0) == 1)
		return (1);
	return (0);
}

int	check_map(t_game *game, char **map_tab)
{
	if (!game->map)
		return (err_msg(game->mapinfo.path, "No mapa?!", 1));
	if (check_map_sides(&game->mapinfo, map_tab) == 1)
		return (err_msg(game->mapinfo.path, "No paredessss?!", 1));
	if (game->mapinfo.height < 3)
		return (err_msg(game->mapinfo.path, "ERROR: Invalid Map.\n", 1));
	if (check_map_elements(game, map_tab) == 1)
		return (1);
	if (check_player_position(game, map_tab) == 1)
		return (1);
	if (check_map_is_at_the_end(&game->mapinfo) == 1)
		return (err_msg(game->mapinfo.path, "ERROR: Invalid Map.\n", 1));
	return (0);
}
