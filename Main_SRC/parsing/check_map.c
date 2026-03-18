/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:32:13 by marada            #+#    #+#             */
/*   Updated: 2026/03/17 17:14:09 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed3d.h"

static int	locate_player_spawn(t_game *ctx, char **grid)
{
	int	row;
	int	col;

	row = 0;
	while (grid[row])
	{
		col = 0;
		while (grid[row][col])
		{
			if (is_player_char(grid[row][col]))
			{
				ctx->player.x = (double)col * BLOCK + BLOCK / 2 - 5;
				ctx->player.y = (double)row * BLOCK + BLOCK / 2 - 5;
				grid[row][col] = '0';
			}
			col++;
		}
		row++;
	}
	if (validate_player_position(ctx, grid) == 1)
		return (msg_err(ctx->mapinfo.path, "ERROR: Position invalid.\n", 1));
	return (0);
}

static int	scan_map_content(t_game *ctx, char **grid)
{
	int	row;
	int	col;

	row = 0;
	ctx->player.dir = '0';
	while (grid[row])
	{
		col = 0;
		while (grid[row][col])
		{
			while (ctx->map[row][col] == ' ' || ctx->map[row][col] == '\t'
				|| (ctx->map[row][col] >= '\v' && ctx->map[row][col] <= '\r'))
				col++;
			if (validate_map_chars(grid[row]) == 1)
				return (msg_err(ctx->mapinfo.path, "Invalid Map.\n", 1));
			if (is_player_char(grid[row][col]) && ctx->player.dir != '0')
				return (msg_err(ctx->mapinfo.path, "Invalid Map.\n", 1));
			if (is_player_char(grid[row][col]) && ctx->player.dir == '0')
				ctx->player.dir = grid[row][col];
			col++;
		}
		row++;
	}
	return (0);
}

static int	verify_vertical_edges(char **grid, int start_col, int last_row)
{
	int	col;

	if (!grid || !grid[0] || !grid[last_row]
		|| !grid[0][start_col] || !grid[last_row][start_col])
		return (1);
	col = start_col;
	while (!is_not_whitespace(grid[0][col]))
		col++;
	while (grid[0][col])
	{
		if (grid[0][col] != '1')
			return (1);
		col++;
	}
	col = 0;
	while (!is_not_whitespace(grid[last_row][col]))
		col++;
	while (grid[last_row][col])
	{
		if (grid[last_row][col] != '1')
			return (1);
		col++;
	}
	return (0);
}

static int	verify_horizontal_edges(t_mapinfo *info, char **grid)
{
	int	row;
	int	col;

	if (verify_vertical_edges(grid, 0, info->height - 1) == 1)
		return (1);
	row = 1;
	while (row < (info->height - 1))
	{
		col = ft_strlen(grid[row]) - 1;
		if (grid[row][col] != '1')
			return (1);
		row++;
	}
	return (0);
}

int	validate_full_map(t_game *ctx, char **grid)
{
	if (!ctx->map)
		return (msg_err(ctx->mapinfo.path, "No mapa?!", 1));
	if (verify_horizontal_edges(&ctx->mapinfo, grid) == 1)
		return (msg_err(ctx->mapinfo.path, "No paredessss?!", 1));
	if (ctx->mapinfo.height < 3)
		return (msg_err(ctx->mapinfo.path, "ERROR: Invalid Map.\n", 1));
	if (scan_map_content(ctx, grid) == 1)
		return (1);
	if (locate_player_spawn(ctx, grid) == 1)
		return (1);
	if (validate_map_end(&ctx->mapinfo) == 1)
		return (msg_err(ctx->mapinfo.path, "ERROR: Invalid Map.\n", 1));
	return (0);
}
