/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:17:56 by marada            #+#    #+#             */
/*   Updated: 2026/01/28 17:20:39 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

size_t	find_biggest_len(t_mapinfo *map, int i)
{
	size_t	biggest_len;

	biggest_len = ft_strlen(map->file[i]);
	while (map->file[i])
	{
		if (ft_strlen(map->file[i]) > biggest_len)
			biggest_len = ft_strlen(map->file[i]);
		i++;
	}
	return (biggest_len);
}

int	count_map_lines(t_game *game, char **file, int i)
{
	int	index_value;
	int	j;

	index_value = i;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r'
		|| file[i][j] == '\v' || file[i][j] == '\f')
			j++;
		if (file[i][j] != '1')
			break ;
		i++;
	}
	game->mapinfo.index_end_of_map = i;
	return (i - index_value);
}

int	fill_map_tab(t_mapinfo *mapinfo, char **map_tab, int index)
{
	int		i;
	int		j;

	mapinfo->width = find_biggest_len(mapinfo, index);
	i = 0;
	while (i < mapinfo->height)
	{
		j = 0;
		map_tab[i] = malloc(sizeof(char) * (mapinfo->width + 1));
		if (!map_tab[i])
			return (err_msg(NULL, "Mais memorias e tais", 1));
		while (mapinfo->file[index][j] && mapinfo->file[index][j] != '\n')
		{
			map_tab[i][j] = mapinfo->file[index][j];
			j++;
		}	
		while (j < mapinfo->width)
			map_tab[i][j++] = '\0';
		i++;
		index++;
	}
	map_tab[i] = NULL;
	return (0);
}

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
		while (game->map[i][++j])
		{
			if (game->map[i][j] == ' '
				&& j != game->map[i][ft_strlen(game->map[i]) - 1])
				game->map[i][j] = '1';
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
