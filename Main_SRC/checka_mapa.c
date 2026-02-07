/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checka_mapa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:32:13 by marada            #+#    #+#             */
/*   Updated: 2026/02/07 21:18:31 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"


int	check_map_is_at_the_end(t_mapinfo *map)
{
	int	i;
	int	j;

	i = map->index_end_of_map;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (map->file[i][j] != ' ' && map->file[i][j] != '\t'
				&& map->file[i][j] != '\r' && map->file[i][j] != '\n'
				&& map->file[i][j] != '\v' && map->file[i][j] != '\f')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_a_white_space(char c)
{
	if (c != ' ' && c != '\t' && c != '\r'
		&& c != '\n' && c != '\v' && c != '\f')
		return (1);
	else
		return (0);
}

int	check_position_is_valid(t_game *game, char **map_tab)
{
	int	i;
	int	j;

	if(game->player.y == 0 && game->player.x == 0)
		return (1);
	i = (int)(game->player.y / BLOCK);
	j = (int)(game->player.x / BLOCK);
	if (ft_strlen(map_tab[i - 1]) < (size_t)j
		|| ft_strlen(map_tab[i + 1]) < (size_t)j
		|| is_a_white_space(map_tab[i][j - 1]) == 0
		|| is_a_white_space(map_tab[i][j + 1]) == 0
		|| is_a_white_space(map_tab[i - 1][j]) == 0
		|| is_a_white_space(map_tab[i + 1][j]) == 0)
		return (1);
	return (0);
}

int	check_player_position(t_game *game, char **map_tab)
{
	int	i;
	int	j;

	i = 0;
	while (map_tab[i])
	{
		j = 0;
		while (map_tab[i][j])
		{
			if (ft_strchr("P", map_tab[i][j]))
			{
				game->player.x = (double)j * BLOCK + BLOCK / 2 - 5;
				game->player.y = (double)i * BLOCK + BLOCK / 2 - 5;
				map_tab[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (check_position_is_valid(game, map_tab) == 1)
		return (err_msg(game->mapinfo.path, "Tao me matando do coracao(com  sedilha no c)", 1));
	return (0);
}

int	check_map_elements(t_game *game, char **map_tab)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map_tab[i] != NULL)
	{
		j = 0;
		while (map_tab[i][j])
		{
			while (game->map[i][j] == ' ' || game->map[i][j] == '\t'
			|| (game->map[i][j] >= '\v' && game->map[i][j] <= '\r'))
				j++;
			if (!(ft_strchr("10PAF", map_tab[i][j])))
				return (err_msg(game->mapinfo.path, "Nada dessas letras estranhas", 1));
			if (ft_strchr("P", map_tab[i][j]) && player != 0)
				return (err_msg(game->mapinfo.path, "Muitos players", 1));
			if (ft_strchr("P", map_tab[i][j]) && player == 0)
				player++;
			j++;
		}
		i++;
	}
	return (0);
}

int	check_top_or_bottom(char **map_tab, int i, int j)
{
	if (!map_tab || !map_tab[i] || !map_tab[i][j])
		return (1);
	while (map_tab[i][j] == ' ' || map_tab[i][j] == '\t'
	|| map_tab[i][j] == '\r' || map_tab[i][j] == '\v'
	|| map_tab[i][j] == '\f')
		j++;
	while (map_tab[i][j])
	{
		if (map_tab[i][j] != '1')
			return (1);
		j++;
	}
	return (0);
}

int	check_map_sides(t_mapinfo *map, char **map_tab)
{
	int	i;
	int	j;

	if (check_top_or_bottom(map_tab, 0, 0) == 1)
		return (1);
	i = 1;
	while (i < (map->height - 1))
	{
		j = ft_strlen(map_tab[i]) - 1;
		if (map_tab[i][j] != '1')
			return (1);
		i++;
	}
	if (check_top_or_bottom(map_tab, i, 0) == 1)
		return (1);
	return (0);
}

int	check_map(t_game *game, char **map_tab)
{
	if (!game->map)
		return (err_msg(game->mapinfo.path, "No mapa?!", 1));
	if (check_map_sides(&game->mapinfo, map_tab) == 1)
		return (err_msg(game->mapinfo.path, "No paredessss?!", 1));
	if (game->mapinfo.height < 3)
		return (err_msg(game->mapinfo.path, "Esse mapa ta meio pequeno nao?", 1));
	if (check_map_elements(game, map_tab) == 1)
		return (1);
	if (check_player_position(game, map_tab) == 1)
		return (1);
	if (check_map_is_at_the_end(&game->mapinfo) == 1)
		return (err_msg(game->mapinfo.path, "Tais e tais sabes como e(com acento)", 1));
	return (0);
}
