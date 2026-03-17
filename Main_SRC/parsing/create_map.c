/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:17:56 by marada            #+#    #+#             */
/*   Updated: 2026/03/17 19:04:42 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

static int	extract_map_data(t_game *game_data, char **file_content, int start_idx)
{
	game_data->mapinfo.height = count_map_rows(game_data, file_content, start_idx);
	game_data->map = malloc(sizeof(char *) * (game_data->mapinfo.height + 1));
	if (!game_data->map)
		return (msg_err(NULL, "Memory allocation failed, bruh!", 1));
	if (populate_map_array(&game_data->mapinfo, game_data->map, start_idx) == 1)
		return (1);
	return (0);
}

static void	convert_spaces_to_walls(t_game *game_data)
{
	int	row;
	int	col;

	row = 0;
	while (game_data->map[row])
	{
		col = 0;
		while (!is_not_whitespace(game_data->map[row][col]))
			col++;
		while (game_data->map[row][col])
		{
			if (game_data->map[row][col] == ' '
				&& col != (int)ft_strlen(game_data->map[row]) - 1)
				game_data->map[row][col] = '1';
			col++;
		}
		row++;
	}
}

int	initialize_map(t_game *game_data, char **file_content, int start_idx)
{
	if (extract_map_data(game_data, file_content, start_idx) == 1)
		return (1);
	convert_spaces_to_walls(game_data);
	return (0);
}
