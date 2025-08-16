/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/16 13:23:24 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Verifica si una posición es válida (no hay pared)
static int	is_valid_position(t_g *g, double x, double y)
{
	int	map_x;
	int	map_y;

	if (!g || !g->map)
		return (0);
	if (g->map_width <= 0 || g->map_height <= 0)
		return (0);
	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= g->map_width || map_y < 0
		|| map_y >= g->map_height)
		return (0);
	if (!g->map[map_y])
		return (0);
	if (g->map[map_y][map_x] == '1')
		return (0);
	return (1);
}

static void	calculate_movement(int keycode, t_g *g, double *new_x,
		double *new_y)
{
	if (!g || !new_x || !new_y)
		return ;
	if (keycode == KEY_W)
	{
		*new_x += g->dir_x * MOVE_SPEED;
		*new_y += g->dir_y * MOVE_SPEED;
	}
	else if (keycode == KEY_S)
	{
		*new_x -= g->dir_x * MOVE_SPEED;
		*new_y -= g->dir_y * MOVE_SPEED;
	}
	else if (keycode == KEY_A)
	{
		*new_x += g->dir_y * MOVE_SPEED;
		*new_y -= g->dir_x * MOVE_SPEED;
	}
	else if (keycode == KEY_D)
	{
		*new_x -= g->dir_y * MOVE_SPEED;
		*new_y += g->dir_x * MOVE_SPEED;
	}
}

void	move_player(int keycode, t_g *g)
{
	double	new_x;
	double	new_y;

	if (!g)
		return ;
	new_x = g->player_x;
	new_y = g->player_y;
	calculate_movement(keycode, g, &new_x, &new_y);
	if (is_valid_position(g, new_x, g->player_y))
		g->player_x = new_x;
	if (is_valid_position(g, g->player_x, new_y))
		g->player_y = new_y;
}

void	rotate_view(int keycode, t_g *g)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotation;

	if (keycode == KEY_LEFT)
		rotation = -ROT_SPEED;
	else if (keycode == KEY_RIGHT)
		rotation = ROT_SPEED;
	else
		return ;
	old_dir_x = g->dir_x;
	g->dir_x = g->dir_x * cos(rotation) - g->dir_y
		* sin(rotation);
	g->dir_y = old_dir_x * sin(rotation) + g->dir_y * cos(rotation);
	old_plane_x = g->plane_x;
	g->plane_x = g->plane_x * cos(rotation) - g->plane_y
		* sin(rotation);
	g->plane_y = old_plane_x * sin(rotation) + g->plane_y
		* cos(rotation);
}
