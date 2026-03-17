/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:49:09 by marada            #+#    #+#             */
/*   Updated: 2026/03/17 17:08:14 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

static int	tab_len(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

static int	*parse_rgb_values(char *line)
{
	char	**split;
	int		*rgb;
	int		i;

	split = ft_split(line, ',');
	if (!split)
		return (NULL);
	if (tab_len(split) != 3)
		return (free_tab((void **)split), NULL);
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		return (free_tab((void **)split), NULL);
	i = -1;
	while (++i < 3)
	{
		if (has_no_digits(split[i]))
			return (free_tab((void **)split), free(rgb), NULL);
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (free_tab((void **)split), free(rgb), NULL);
	}
	free_tab((void **)split);
	return (rgb);
}

static int	parse_color_line(t_game *game, t_texinfo *tex, char *line, int i)
{
	int	*rgb;

	if (!line[i + 1])
		return (msg_err(game->mapinfo.path, "Color Invalid\n", 2));
	rgb = parse_rgb_values(line + i + 1);
	if (!rgb)
		return (msg_err(game->mapinfo.path, "Color Invalid\n", 2));
	if (line[i] == 'C' && !tex->ceiling)
		tex->ceiling = rgb;
	else if (line[i] == 'F' && !tex->floor)
		tex->floor = rgb;
	else
		return (free(rgb), msg_err(game->mapinfo.path, "Color Invalid\n", 2));
	return (0);
}

static int	parse_line_info(t_game *game, char **map, int y, int x)
{
	char	c;

	c = map[y][x];

	if (ft_isdigit(c))
	{
		if (create_map(game, map, y))
			return (ft_putstr_fd("Sem mapa?!\n", 2), 1);
		return (0);
	}
	if (!ft_isprint(c))
		return (4);
	if (map[y][x + 1] && ft_isprint(map[y][x + 1]))
	{
		if (assign_texture_path(&game->texinfo, map[y], x) == 2)
			return (ft_putstr_fd("Sem texturas?!\n", 2), 1);
		return (3);
	}
	if (parse_color_line(game, &game->texinfo, map[y], x) == 2)
		return (1);
	return (3);
}

int	parse_file_info(t_game *game, char **map)
{
	int	y;
	int	x;
	int	ret;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			while (map[y][x] == ' ' || map[y][x] == '\t' || map[y][x] == '\n')
				x++;
			if (!map[y][x])
				break ;
			ret = parse_line_info(game, map, y, x);
			if (ret == 3)
				break ;
			if (ret == 1)
				return (1);
			if (ret == 0)
				return (0);

			x++;
		}
		y++;
	}
	return (0);
}