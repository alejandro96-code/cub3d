/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:00:00 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/06 17:00:00 by alejanr2         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

// Verifica si una posición es válida (no hay pared)
static int	is_valid_position(t_cub_config *cfg, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	
	// Verificar límites del mapa
	if (map_x < 0 || map_x >= cfg->map_width || 
		map_y < 0 || map_y >= cfg->map_height)
		return (0);
	
	// Verificar si hay una pared
	if (cfg->map[map_y][map_x] == '1')
		return (0);
	
	return (1);
}

void	move_player(int keycode, t_cub_config *cfg, t_player *player)
{
	double	new_x;
	double	new_y;

	new_x = player->x;
	new_y = player->y;

	if (keycode == KEY_W)
	{
		new_x += player->dir_x * MOVE_SPEED;
		new_y += player->dir_y * MOVE_SPEED;
	}
	else if (keycode == KEY_S)
	{
		new_x -= player->dir_x * MOVE_SPEED;
		new_y -= player->dir_y * MOVE_SPEED;
	}
	else if (keycode == KEY_A)
	{
		new_x += player->dir_y * MOVE_SPEED;  // Perpendicular a la dirección
		new_y -= player->dir_x * MOVE_SPEED;
	}
	else if (keycode == KEY_D)
	{
		new_x -= player->dir_y * MOVE_SPEED;  // Perpendicular a la dirección
		new_y += player->dir_x * MOVE_SPEED;
	}

	// Verificar colisiones antes de mover
	if (is_valid_position(cfg, new_x, player->y))
		player->x = new_x;
	if (is_valid_position(cfg, player->x, new_y))
		player->y = new_y;
}

void	rotate_view(int keycode, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotation;

	if (keycode == KEY_LEFT)
		rotation = -ROT_SPEED;
	else if (keycode == KEY_RIGHT)
		rotation = ROT_SPEED;
	else
		return;

	// Rotar vector de dirección
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rotation) - player->dir_y * sin(rotation);
	player->dir_y = old_dir_x * sin(rotation) + player->dir_y * cos(rotation);

	// Rotar plano de cámara
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rotation) - player->plane_y * sin(rotation);
	player->plane_y = old_plane_x * sin(rotation) + player->plane_y * cos(rotation);
}
