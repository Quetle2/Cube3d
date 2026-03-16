/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:35:20 by marada            #+#    #+#             */
/*   Updated: 2026/03/16 19:43:54 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

void	init_player_direlao(t_player *player)
{
	if (player->dir == 'N')
		player->angle = 1.5 * PI;
	else if (player->dir == 'W')
		player->angle = PI;
	else if (player->dir == 'E')
		player->angle = 0;
	else if (player->dir == 'S')
		player->angle = PI / 2;
}

int	parse_argumentos(t_game *game, char **av)
{
	int	fd;
	int		row;
	int		i;
	size_t	column;
	char	*line;
	int		line_count;

	line_count = 0;
	i = 0;
	row = 0;
	column = 0;
	if (is_dir(av[1]))
		fecha_com_msg(game, "DIRETORIO?!", 1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		fecha_com_msg(game, "N Abre?!", 1);
	close(fd);
	if (1 && !is_cub_file(av[1]))
		fecha_com_msg(game, "N e .CUB?!", 1);

	game->mapinfo.path = av[1];
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_putstr_fd("n abriu be like", 2);
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
	game->mapinfo.file = ft_calloc(line_count + 1, sizeof(char *));
	if (!(game->mapinfo.file))
		ft_putstr_fd("Nao consegui alocar memorias\n", 2);
	game->mapinfo.fd = open(av[1], O_RDONLY);
	if (game->mapinfo.fd < 0)
		ft_putstr_fd("No opens?!\n", 2);
	else
	{
		enche_tab(row, column, i, game);
		close(game->mapinfo.fd);
	}
	// if (get_file_inf(game, game->mapinfo.file))
	// 	clean_exit(game, 1);
	if (parse_file_info(game, game->mapinfo.file))
		clean_exit(game, 1);
//
	if (check_map(game, game->map) == 1)
		return (clean_exit(game, 1), 1);
	init_player_direlao(&game->player);
	return (0);
}
