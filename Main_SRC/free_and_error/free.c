/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:14:49 by marada            #+#    #+#             */
/*   Updated: 2026/03/18 13:31:27 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

int	close_com(t_game *game)
{
	clean_saida(game, 1);
	return (1);
}

static void	free_game(t_game *game)
{
	free_texinfo(&game->texinfo);
	free_colors(&game->color);
	if (game->textures)
		free_textures(game->textures);
	if (game->mapinfo.fd > 0)
		close(game->mapinfo.fd);
	if (game->mapinfo.file)
		free_tab((void **)game->mapinfo.file);
	if (game->map)
		free_tab((void **)game->map);
	if (game->bola)
		free_bola(game->bola);
}

static int	free_data(t_game *game)
{
	free_game(game);
	return (1);
}

void	clean_saida(t_game *game, int code)
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
