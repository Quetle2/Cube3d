/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:14:49 by marada            #+#    #+#             */
/*   Updated: 2026/03/05 04:27:15 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

int	close_com(t_game *game)
{
	clean_exit(game, 1);
	return (1);
}

void	free_map(t_game *game)
{
	free_texinfo(&game->texinfo);
	if (game->textures)
		free_textures(game->textures);
	if (game->mapinfo.fd > 0)
		close(game->mapinfo.fd);
	if (game->mapinfo.file)
		free_tab((void **)game->mapinfo.file);
	if (game->map)
		free_tab((void **)game->map);
}

int	free_data(t_game *game)
{
	free_map(game);
	return (1);
}

void	clean_exit(t_game *game, int code)
{
	if (!game)
		exit(code);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_image(game->mlx, game->img.img);
		mlx_destroy_display(game->mlx);
		mlx_loop_end(game->mlx);
		free(game->mlx);
	}
	free_data(game);
	exit(code);
}

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}
