/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 21:36:14 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/17 11:12:34 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

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
		while (!is_a_white_space(file[i][j]))
			j++;
		if (file[i][j] != '1')
			break ;
		i++;
	}
	game->mapinfo.index_end_of_map = i;
	return (i - index_value);
}

char	*copy_line(char *line, int width)
{
	int		x;
	char	*copy;

	copy = malloc(sizeof(char) * (width + 1));
	if (!copy)
		return (NULL);
	x = 0;
	while (line[x] && line[x] != '\n')
	{
		copy[x] = line[x];
		x++;
	}
	while (x <= width)
	{
		copy[x] = '\0';
		x++;
	}
	return (copy);
}

int	fill_map_tab(t_mapinfo *mapinfo, char **map_tab, int index)
{
	int		i;

	mapinfo->width = find_biggest_len(mapinfo, index);
	i = 0;
	while (i < mapinfo->height)
	{
		map_tab[i] = copy_line(mapinfo->file[index], mapinfo->width);
		if (!map_tab[i])
			return (msg_err(NULL, "Mais memorias e tais", 1));
		i++;
		index++;
	}
	map_tab[i] = NULL;
	return (0);
}
