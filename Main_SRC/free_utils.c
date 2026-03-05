/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 04:25:47 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/05 06:27:34 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

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
	free(textures[0][NOTH]);
	free(textures[0][SOTH]);
	free(textures[0][EAST]);
	free(textures[0][WEST]);
	// free(textures[1][NOTH]);
	// free(textures[1][SOTH]);
	// free(textures[1][EAST]);
	// free(textures[1][WEST]);
	// free(textures[2][NOTH]);
	// free(textures[2][SOTH]);
	// free(textures[2][EAST]);
	// free(textures[2][WEST]);
	// free(textures[3][NOTH]);
	// free(textures[3][SOTH]);
	// free(textures[3][EAST]);
	// free(textures[3][WEST]);
	free(textures);
}
