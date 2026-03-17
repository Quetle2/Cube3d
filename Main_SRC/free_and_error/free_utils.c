/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 04:25:47 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/17 16:39:40 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

void	free_texinfo(t_texinfo *texinfo)
{
	if (texinfo->floor)
		free(texinfo->floor);
	if (texinfo->ceiling)
		free(texinfo->ceiling);
	if (texinfo->north)
		free(texinfo->north);
	if (texinfo->south)
		free(texinfo->south);
	if (texinfo->west)
		free(texinfo->west);
	if (texinfo->east)
		free(texinfo->east);
}

void	free_textures(int ***textures)
{
	int		theme;
	int		sprite;

	theme = 0;
	while (theme < 4)
	{
		sprite = 0;
		while (sprite < 4)
		{
			free(textures[theme][sprite]);
			sprite++;
		}
		free(textures[theme]);
		theme++;
	}
	free(textures[4][0]);
	free(textures[4]);
	free(textures);
}

void	free_colors(t_color *color)
{
	free(color->door);
	free(color->open);
	free(color->square);
}
