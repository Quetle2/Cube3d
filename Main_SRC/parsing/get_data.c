/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:49:09 by marada            #+#    #+#             */
/*   Updated: 2026/03/16 19:42:56 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

// int	*copy_into_rgb_array(char **rgb_to_convert, int *rgb)
// {
// 	int		i;

// 	i = -1;
// 	while (rgb_to_convert[++i])
// 	{
// 		rgb[i] = ft_atoi(rgb_to_convert[i]);
// 		if (rgb[i] == -1 || no_digit(rgb_to_convert[i]) == 1
// 			|| rgb[i] < 0 || rgb[i] > 255)
// 		{
// 			free_tab((void **)rgb_to_convert);
// 			free(rgb);
// 			return (0);
// 		}
// 	}
// 	free_tab((void **)rgb_to_convert);
// 	return (rgb);
// }

// int	*set_rgb_colors(char *line)
// {
// 	char	**rgb_to_convert;
// 	int		*rgb;
// 	int		count;

// 	rgb_to_convert = ft_split(line, ',');
// 	count = 0;
// 	while (rgb_to_convert[count])
// 		count++;
// 	if (count != 3)
// 	{
// 		free_tab((void **)rgb_to_convert);
// 		return (0);
// 	}
// 	rgb = malloc(sizeof(int) * 3);
// 	if (!rgb)
// 	{
// 		msg_err(NULL, "Falta de memoria e tais", 0);
// 		return (0);
// 	}
// 	return (copy_into_rgb_array(rgb_to_convert, rgb));
// }

// int	fill_color_textures(t_game *game, t_texinfo *textures, char *line, int j)
// {
// 	if (line[j + 1] && ft_isprint(line[j + 1]))
// 		return (msg_err(game->mapinfo.path, "Color Invalid\n", 2));
// 	if (!textures->ceiling && line[j] == 'C')
// 	{
// 		textures->ceiling = set_rgb_colors(line + j + 1);
// 		if (textures->ceiling == 0)
// 			return (msg_err(game->mapinfo.path, "Color Invalid\n", 2));
// 	}
// 	else if (!textures->floor && line[j] == 'F')
// 	{
// 		textures->floor = set_rgb_colors(line + j + 1);
// 		if (textures->floor == 0)
// 			return (msg_err(game->mapinfo.path, "Color Invalid\n", 2));
// 	}
// 	else
// 		return (msg_err(game->mapinfo.path, "Color Invalid\n", 2));
// 	return (0);
// }

// int	get_inf(t_game *game, char **map, int i, int j)
// {
// 	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
// 	{
// 		if (map[i][j + 1] && ft_isprint(map[i][j + 1])
// 			&& !ft_isdigit(map[i][j]))
// 		{
// 			if (fill_direction_textures(&game->texinfo, map[i], j) == 2)
// 				return (ft_putstr_fd("Sem texturas?!\n", 2), 1);
// 			return (3);
// 		}
// 		else
// 		{
// 			if (fill_color_textures(game, &game->texinfo, map[i], j) == 2)
// 				return (1);
// 			return (3);
// 		}
// 	}
// 	else if (ft_isdigit(map[i][j]))
// 	{
// 		if (create_map(game, map, i) == 1)
// 			return (ft_putstr_fd("Sem mapa?!\n", 2), 1);
// 		return (0);
// 	}
// 	return (4);
// }

// int	get_file_inf(t_game *game, char **map)
// {
// 	int	y;
// 	int	x;
// 	int	ret;

// 	y = -1;
// 	while (map[++y])
// 	{
// 		x = -1;
// 		while (map[y][++x])
// 		{
// 			while (map[y][x] == ' ' || map[y][x] == '\t' || map[y][x] == '\n')
// 				x++;
// 			ret = get_inf(game, map, y, x);
// 			if (ret == 3)
// 				break ;
// 			else if (ret == 1)
// 				return (1);
// 			else if (ret == 0)
// 				return (0);
// 		}
// 	}
// 	return (0);
// }

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int	*parse_rgb_values(char *line)
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

	i = 0;
	while (i < 3)
	{
		if (no_digit(split[i]))
			return (free_tab((void **)split), free(rgb), NULL);
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (free_tab((void **)split), free(rgb), NULL);
		i++;
	}
	free_tab((void **)split);
	return (rgb);
}

int	parse_color_line(t_game *game, t_texinfo *tex, char *line, int i)
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

int	parse_line_info(t_game *game, char **map, int y, int x)
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
		if (fill_direction_textures(&game->texinfo, map[y], x) == 2)
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