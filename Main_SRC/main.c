/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:24:52 by marada            #+#    #+#             */
/*   Updated: 2026/03/25 11:11:02 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubed3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (msg_err("Usage", USAGE_ERR, 1));
	init_game(&game);
	init_colors(&game);
	if (parse_argumentos(&game, av) != 0)
		return (1);
	init_textures(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 1L << 17, close_com, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
