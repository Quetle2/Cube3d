/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 04:25:47 by jobraga-          #+#    #+#             */
/*   Updated: 2026/03/05 04:26:07 by jobraga-         ###   ########.fr       */
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

void	free_textures(int **textures)
{
	free(textures[NOTH]);
	free(textures[SOTH]);
	free(textures[EAST]);
	free(textures[WEST]);
	free(textures);
}
