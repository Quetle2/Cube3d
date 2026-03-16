/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:49:09 by marada            #+#    #+#             */
/*   Updated: 2026/03/16 16:25:51 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

int	*copy_into_rgb_array(char **rgb_to_convert, int *rgb)
{
	int		i;

	i = -1;
	while (rgb_to_convert[++i])
	{
		rgb[i] = ft_atoi(rgb_to_convert[i]);
		if (rgb[i] == -1 || no_digit(rgb_to_convert[i]) == 1
			|| rgb[i] < 0 || rgb[i] > 255)
		{
			free_tab((void **)rgb_to_convert);
			free(rgb);
			return (0);
		}
	}
	free_tab((void **)rgb_to_convert);
	return (rgb);
}

int	*set_rgb_colors(char *line)
{
	char	**rgb_to_convert;
	int		*rgb;
	int		count;

	rgb_to_convert = ft_split(line, ',');
	count = 0;
	while (rgb_to_convert[count])
		count++;
	if (count != 3)
	{
		free_tab((void **)rgb_to_convert);
		return (0);
	}
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		msg_err(NULL, "Falta de memoria e tais", 0);
		return (0);
	}
	return (copy_into_rgb_array(rgb_to_convert, rgb));
}

int	fill_color_textures(t_game *game, t_texinfo *textures, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1]))
		return (msg_err(game->mapinfo.path, "Color Invalid\n", 2));
	if (!textures->ceiling && line[j] == 'C')
	{
		textures->ceiling = set_rgb_colors(line + j + 1);
		if (textures->ceiling == 0)
			return (msg_err(game->mapinfo.path, "Color Invalid\n", 2));
	}
	else if (!textures->floor && line[j] == 'F')
	{
		textures->floor = set_rgb_colors(line + j + 1);
		if (textures->floor == 0)
			return (msg_err(game->mapinfo.path, "Color Invalid\n", 2));
	}
	else
		return (msg_err(game->mapinfo.path, "Color Invalid\n", 2));
	return (0);
}
