/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:35:20 by marada            #+#    #+#             */
/*   Updated: 2026/03/04 22:15:43 by jobraga-         ###   ########.fr       */
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
	game->mapinfo.file = ft_calloc(game->mapinfo.line_count
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

void	init_player_direlao(t_player *player)
{
	if (player->dir == 'N')
		player->angle = PI / 2;
	else if (player->dir == 'W')
		player->angle = 0;
	else if (player->dir == 'E')
		player->angle = PI;
	else if (player->dir == 'S')
		player->angle = 1.5 * PI;
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
	init_player_direlao(&game->player);
	return (0);
}
