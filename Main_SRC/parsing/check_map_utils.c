/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:40:08 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/17 19:04:47 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

int	validate_map_end(t_mapinfo *data)
{
	int	row;
	int	col;

	row = data->index_end_of_map;
	while (data->file[row])
	{
		col = 0;
		while (data->file[row][col])
		{
			if (data->file[row][col] != ' ' && data->file[row][col] != '\t'
				&& data->file[row][col] != '\r' && data->file[row][col] != '\n'
				&& data->file[row][col] != '\v' && data->file[row][col] != '\f')
				return (1);
			col++;
		}
		row++;
	}
	return (0);
}

int	is_not_whitespace(char c)
{
	if (c != ' ' && c != '\t' && c != '\r'
		&& c != '\n' && c != '\v' && c != '\f')
		return (1);
	return (0);
}

int	validate_player_position(t_game *game, char **grid)
{
	int	row;
	int	col;

	if (game->player.dir == '0')
		return (1);
	row = (int)(game->player.y / BLOCK);
	col = (int)(game->player.x / BLOCK);
	if (ft_strlen(grid[row - 1]) < (size_t)col
		|| ft_strlen(grid[row + 1]) < (size_t)col
		|| is_not_whitespace(grid[row][col - 1]) == 0
		|| is_not_whitespace(grid[row][col + 1]) == 0
		|| is_not_whitespace(grid[row - 1][col]) == 0
		|| is_not_whitespace(grid[row + 1][col]) == 0)
		return (1);
	return (0);
}

int	validate_map_chars(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] != '1' && str[idx] != '0' && str[idx] != 'N'
			&& str[idx] != 'S' && str[idx] != 'W' && str[idx] != 'E'
			&& str[idx] != 'A' && str[idx] != 'F')
			return (1);
		idx++;
	}
	return (0);
}

int	is_player_char(char c)
{
	if (c == 'N')
		return (1);
	if (c == 'S')
		return (1);
	if (c == 'W')
		return (1);
	if (c == 'E')
		return (1);
	return (0);
}
