/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:32:13 by marada            #+#    #+#             */
/*   Updated: 2026/03/16 18:16:47 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

int	char_player(char player)
{
	if (player == 'N')
		return (1);	
	else if (player == 'S')
		return (1);	
	else if (player == 'W')
		return (1);	
	else if (player == 'E')
		return (1);
	return (0);
}

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
			if (char_player(map_tab[i][j]))
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
		return (msg_err(game->mapinfo.path, "ERROR: Position invalid.\n", 1));
	return (0);
}

int	char_map_check(char *line)
{
	int		p;

	p = 0;
	while (line[p])
	{
		if (line[p] != '1' && line[p] != '0' && line[p] != 'N'
			&& line[p] != 'S' && line[p] != 'W' && line[p] != 'E'
			&& line[p] != 'A' && line[p] != 'F')
			return (1);
		p++;
	}
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
			if (char_map_check(map_tab[i]) == 1)
				return (msg_err(game->mapinfo.path, "Invalid Map.\n", 1));
			if (char_player(map_tab[i][j]) == 1 && game->player.dir != '0')
				return (msg_err(game->mapinfo.path, "Invalid Map.\n", 1));
			if (char_player(map_tab[i][j]) == 1 && game->player.dir == '0')
				game->player.dir = map_tab[i][j];
			j++;
		}
		i++;
	}
	return (0);
}

int	check_top_or_bottom(char **map_tab, int j, int limit)
{	
	if (!map_tab || !map_tab[0] ||!map_tab[limit] || !map_tab[0][j]
		|| !map_tab[limit][j])
		return (1);
	while (!is_a_white_space(map_tab[0][j]))
		j++;
	while (map_tab[0][j])
	{
		if (map_tab[0][j] != '1')
			return (1);
		j++;
	}
	j = 0;
	while (!is_a_white_space(map_tab[limit][j]))
		j++;
	while (map_tab[limit][j])
	{
		if (map_tab[limit][j] != '1')
			return (1);
		j++;
	}
	return (0);
}

int	check_map_sides(t_mapinfo *map, char **map_tab)
{
	int		i;
	int		j;

	if (check_top_or_bottom(map_tab, 0, map->height - 1) == 1)
		return (1);
	i = 1;
	while (i < (map->height - 1))
	{
		j = ft_strlen(map_tab[i]) - 1;
		if (map_tab[i][j] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_map(t_game *game, char **map_tab)
{
	if (!game->map)
		return (msg_err(game->mapinfo.path, "No mapa?!", 1));
	if (check_map_sides(&game->mapinfo, map_tab) == 1)
		return (msg_err(game->mapinfo.path, "No paredessss?!", 1));
	if (game->mapinfo.height < 3)
		return (msg_err(game->mapinfo.path, "ERROR: Invalid Map.\n", 1));
	if (check_map_elements(game, map_tab) == 1)
		return (1);
	if (check_player_position(game, map_tab) == 1)
		return (1);
	if (check_map_is_at_the_end(&game->mapinfo) == 1)
		return (msg_err(game->mapinfo.path, "ERROR: Invalid Map.\n", 1));
	return (0);
}
