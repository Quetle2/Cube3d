/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:49:35 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/17 19:13:23 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

static char	*extract_path_from_line(char *str, int pos)
{
	int		begin;
	int		length;
	char	*result;

	while (str[pos] == ' ' || str[pos] == '\t')
		pos++;
	begin = pos;
	while (str[pos] && str[pos] != ' ' && str[pos] != '\t'
		&& str[pos] != '\n')
		pos++;
	length = pos - begin;
	if (length <= 0)
		return (NULL);
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	ft_memcpy(result, &str[begin], length);
	result[length] = '\0';
	while (str[pos] == ' ' || str[pos] == '\t')
		pos++;
	if (str[pos] && str[pos] != '\n')
		return (free(result), NULL);
	return (result);
}

int	assign_texture_path(t_texinfo *info, char *str, int pos)
{
	char	*value;

	if (!str[pos + 1])
		return (2);
	value = extract_path_from_line(str, pos + 2);
	if (!value)
		return (2);
	if (str[pos] == 'N' && str[pos + 1] == 'O' && !info->north)
		info->north = value;
	else if (str[pos] == 'S' && str[pos + 1] == 'O' && !info->south)
		info->south = value;
	else if (str[pos] == 'W' && str[pos + 1] == 'E' && !info->west)
		info->west = value;
	else if (str[pos] == 'E' && str[pos + 1] == 'A' && !info->east)
		info->east = value;
	else
		return (free(value), 2);
	return (0);
}

int	has_no_digits(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (ft_isdigit(str[idx]))
			return (0);
		idx++;
	}
	return (1);
}

int	*load_texture_pixels(t_game *game, char *file)
{
	t_img	texture;
	int		*pixels;
	int		total;
	int		k;

	init_texture_img(game, &texture, file);
	total = game->texinfo.size * game->texinfo.size;
	pixels = ft_calloc(total, sizeof(int));
	if (!pixels)
		clean_exit(game, msg_err(NULL, "Malloc e tal", 1));
	k = 0;
	while (k < total)
	{
		pixels[k] = texture.addr[k];
		k++;
	}
	mlx_destroy_image(game->mlx, texture.img);
	return (pixels);
}
