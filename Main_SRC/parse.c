/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:35:20 by marada            #+#    #+#             */
/*   Updated: 2026/02/05 19:38:07 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

int	get_number_of_lines(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		err_msg(path, strerror(errno), errno);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
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
			err_msg(NULL, "Erro no malloc", 0);
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

void	parse_data(char *path, t_game *game)
{
	int		row;
	int		i;
	size_t	column;

	i = 0;
	row = 0;
	column = 0;
	game->mapinfo.line_count = get_number_of_lines(path);
	game->mapinfo.path = path;
	game->mapinfo.file = ft_calloc(game->mapinfo.line_count \
			+ 1, sizeof(char *));
	if (!(game->mapinfo.file))
	{
		err_msg(NULL, "Nao consegui alocar memorias", 0);
		return ;
	}
	game->mapinfo.fd = open(path, O_RDONLY);
	if (game->mapinfo.fd < 0)
		err_msg(path, strerror(errno), 1);
	else
	{
		fill_tab(row, column, i, game);
		close(game->mapinfo.fd);
	}
}

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

int	check_file(char *arg, int cub)
{
	int	fd;

	if (is_dir(arg))
		return (err_msg(arg, "File is a directory", 1));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (err_msg(arg, strerror(errno), 1));
	close(fd);
	if (cub && !is_cub_file(arg))
		return (err_msg(arg, "File is not a .cub", 1));
	if (!cub && !is_xpm_file(arg))
		return (err_msg(arg, "File is not a xpm", 1));
	return (0);
}

int	parse_args(t_game *game, char **av)
{
	if (check_file(av[1], 1) == 1)
		clean_exit(game, 1);
	parse_data(av[1], game);
	if (get_file_data(game, game->mapinfo.file) == 1)
		return (free_data(game));
	if (check_map(game, game->map) == 1)
		return (free_data(game));
	return (0);
}
