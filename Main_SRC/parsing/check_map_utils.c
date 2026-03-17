/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:40:08 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/17 01:54:10 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

int	check_map_is_at_the_end(t_mapinfo *map)
{
	int	i;
	int	j;

	i = map->index_end_of_map;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (map->file[i][j] != ' ' && map->file[i][j] != '\t'
				&& map->file[i][j] != '\r' && map->file[i][j] != '\n'
				&& map->file[i][j] != '\v' && map->file[i][j] != '\f')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_a_white_space(char c)
{
	if (c != ' ' && c != '\t' && c != '\r'
		&& c != '\n' && c != '\v' && c != '\f')
		return (1);
	else
		return (0);
}

int	check_position_is_valid(t_game *game, char **map_tab)
{
	int	i;
	int	j;

	if (game->player.dir == '0')
		return (1);
	i = (int)(game->player.y / BLOCK);
	j = (int)(game->player.x / BLOCK);
	if (ft_strlen(map_tab[i - 1]) < (size_t)j
		|| ft_strlen(map_tab[i + 1]) < (size_t)j
		|| is_a_white_space(map_tab[i][j - 1]) == 0
		|| is_a_white_space(map_tab[i][j + 1]) == 0
		|| is_a_white_space(map_tab[i - 1][j]) == 0
		|| is_a_white_space(map_tab[i + 1][j]) == 0)
		return (1);
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
