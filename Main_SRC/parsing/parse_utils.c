/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 20:01:55 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/17 19:10:03 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

int	is_directory(char *path)
{
	int		fd;
	int		result;

	result = 0;
	fd = open(path, 00200000);
	if (fd >= 0)
	{
		close(fd);
		result = 1;
	}
	return (result);
}

int	is_cub_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if ((filename[len - 3] != 'c' || filename[len - 2] != 'u'
			|| filename[len - 1] != 'b'
			|| filename[len - 4] != '.'))
		return (0);
	return (1);
}

int	is_xpm_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if ((filename[len - 3] != 'x' || filename[len - 2] != 'p'
			|| filename[len - 1] != 'm'
			|| filename[len - 4] != '.'))
		return (0);
	return (1);
}

void	fill_map_lines(int row_idx, int col_idx,
	int char_idx, t_game *game_data)
{
	char	*line;

	line = get_next_line(game_data->mapinfo.fd);
	while (line != NULL)
	{
		game_data->mapinfo.file[row_idx]
			= ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!game_data->mapinfo.file[row_idx])
		{
			msg_err(NULL, "Malloc failed, bruh!", 0);
			return (free_tab((void **)game_data->mapinfo.file));
		}
		while (line[char_idx] != '\0')
			game_data->mapinfo.file[row_idx][col_idx++] = line[char_idx++];
		game_data->mapinfo.file[row_idx++][col_idx] = '\0';
		col_idx = 0;
		char_idx = 0;
		free(line);
		line = get_next_line(game_data->mapinfo.fd);
	}
	game_data->mapinfo.file[row_idx] = NULL;
}
