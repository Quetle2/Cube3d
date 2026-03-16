/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 20:01:55 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/16 15:11:49 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

int	is_dir(char *arg)
{
	int		fd;
	int		ret;

	ret = 0;
	fd = open(arg, 00200000);
	if (fd >= 0)
	{
		close (fd);
		ret = 1;
	}
	return (ret);
}

int	is_cub_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'c' || arg[len - 2] != 'u'
			|| arg[len - 1] != 'b'
			|| arg[len - 4] != '.'))
		return (0);
	return (1);
}

int	is_xpm_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'x' || arg[len - 2] != 'p'
			|| arg[len - 1] != 'm'
			|| arg[len - 4] != '.'))
		return (0);
	return (1);
}

void	fill_tab(int row, int column, int i, t_game *game)
{
	char	*line;

	line = get_next_line(game->mapinfo.fd);
	while (line != NULL)
	{
		game->mapinfo.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!game->mapinfo.file[row])
		{
			msg_err(NULL, "Erro no malloc", 0);
			return (free_tab((void **)game->mapinfo.file));
		}
		while (line[i] != '\0')
			game->mapinfo.file[row][column++] = line[i++];
		game->mapinfo.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(game->mapinfo.fd);
	}
	game->mapinfo.file[row] = NULL;
}
