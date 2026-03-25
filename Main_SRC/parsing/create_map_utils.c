/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 21:36:14 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/18 15:48:28 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

static size_t	get_max_line_length(t_mapinfo *map_data, int start_idx)
{
	size_t	max_length;

	max_length = ft_strlen(map_data->file[start_idx]);
	while (map_data->file[start_idx])
	{
		if (ft_strlen(map_data->file[start_idx]) > max_length)
			max_length = ft_strlen(map_data->file[start_idx]);
		start_idx++;
	}
	return (max_length);
}

static char	*duplicate_line(char *src_line, int target_width)
{
	int		pos;
	char	*new_line;

	new_line = malloc(sizeof(char) * (target_width + 1));
	if (!new_line)
		return (NULL);
	pos = 0;
	while (src_line[pos] && src_line[pos] != '\n')
	{
		new_line[pos] = src_line[pos];
		pos++;
	}
	while (pos <= target_width)
		new_line[pos++] = '\0';
	return (new_line);
}

int	populate_map_array(t_mapinfo *map_data, char **map_array, int start_idx)
{
	int	row;

	map_data->width = get_max_line_length(map_data, start_idx);
	row = 0;
	while (row < map_data->height)
	{
		map_array[row]
			= duplicate_line(map_data->file[start_idx], map_data->width);
		if (!map_array[row])
			return (msg_err(NULL, "Memory issues bruh", 1));
		row++;
		start_idx++;
	}
	map_array[row] = NULL;
	return (0);
}

int	count_map_rows(t_game *game_data, char **file_content, int start_idx)
{
	int	initial_idx;
	int	col;

	initial_idx = start_idx;
	while (file_content[start_idx])
	{
		col = 0;
		while (!is_not_whitespace(file_content[start_idx][col]))
			col++;
		if (file_content[start_idx][col] != '1')
			break ;
		start_idx++;
	}
	game_data->mapinfo.index_end_of_map = start_idx;
	return (start_idx - initial_idx);
}
