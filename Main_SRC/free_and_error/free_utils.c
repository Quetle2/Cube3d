/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 04:25:47 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/18 13:31:33 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

void	free_bola(t_list *bolas)
{
	t_list	*tmp;

	while (bolas != NULL)
	{
		tmp = bolas->next;
		if (bolas->content != NULL)
			free(bolas->content);
		free(bolas);
		bolas = tmp;
	}
}

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
