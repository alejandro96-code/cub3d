/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 00:58:05 by ybahri            #+#    #+#             */
/*   Updated: 2025/09/10 16:49:18 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_position_free(t_g *g, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= g->map_width || map_y < 0
		|| map_y >= g->map_height)
		return (0);
	return (g->map[map_y][map_x] == '0');
}

static int	is_valid_position(t_g *g, double x, double y)
{
	int		map_x;
	int		map_y;
	char	c;

	if (!g)
		return (0);
	if (!is_map_position_free(g, x - COLLISION_MARGIN, y - COLLISION_MARGIN)
		|| !is_map_position_free(g, x + COLLISION_MARGIN, y - COLLISION_MARGIN)
		|| !is_map_position_free(g, x - COLLISION_MARGIN, y + COLLISION_MARGIN)
		|| !is_map_position_free(g, x + COLLISION_MARGIN, y + COLLISION_MARGIN))
		return (0);
	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= g->map_width || map_y < 0
		|| map_y >= g->map_height)
		return (0);
	c = g->map[map_y][map_x];
	if (c == '0')
		return (1);
	return (0);
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
	g->dir_x = g->dir_x * cos(rotation) - g->dir_y * sin(rotation);
	g->dir_y = old_dir_x * sin(rotation) + g->dir_y * cos(rotation);
	old_plane_x = g->plane_x;
	g->plane_x = g->plane_x * cos(rotation) - g->plane_y * sin(rotation);
	g->plane_y = old_plane_x * sin(rotation) + g->plane_y * cos(rotation);
}
