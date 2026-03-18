/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:35:20 by marada            #+#    #+#             */
/*   Updated: 2026/03/18 15:22:05 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

static void	validate_input_file(t_game *game, char *path)
{
	int	fd;

	if (is_directory(path))
		fecha_com_msg(game, "DIRETORIO?!", 1);
	if (!is_cub_extension(path))
		fecha_com_msg(game, "N e .CUB?!", 1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		fecha_com_msg(game, "N Abre?!", 1);
	close(fd);
}

static int	count_file_lines(char *path)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static int	load_file_into_memory(t_game *game, int line_count)
{
	game->mapinfo.file = ft_calloc(line_count + 1, sizeof(char *));
	if (!game->mapinfo.file)
		return (1);
	game->mapinfo.fd = open(game->mapinfo.path, O_RDONLY);
	if (game->mapinfo.fd < 0)
		return (1);
	fill_map_lines(0, 0, 0, game);
	close(game->mapinfo.fd);
	return (0);
}

static int	process_file_data(t_game *game)
{
	if (parse_file_info(game, game->mapinfo.file))
		return (1);
	if (validate_full_map(game, game->map))
		return (1);
	return (0);
}

int	parse_argumentos(t_game *game, char **av)
{
	int	line_count;

	validate_input_file(game, av[1]);
	game->mapinfo.path = av[1];
	line_count = count_file_lines(av[1]);
	if (line_count <= 0)
		return (1);
	if (load_file_into_memory(game, line_count))
		return (1);
	if (process_file_data(game))
		return (clean_saida(game, 1), 1);
	init_player_direlao(&game->player);
	return (0);
}
