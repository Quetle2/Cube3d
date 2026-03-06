/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 04:25:47 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/06 01:05:59 by jobraga-         ###   ########.fr       */
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
		theme++;
	}
	free(textures);
}
