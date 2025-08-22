/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:27:04 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/22 15:27:06 by ybahri           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

// Función simple para rotar la cámara
static void	rotate_camera_mouse(t_g *g, double rotation)
{
	double	old_dir_x;
	double	old_plane_x;

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

// Función del mouse usando movimiento relativo
int	mouse_move(int x, int y, t_g *g)
{
	double	rotation;
	int		delta_x;

	(void)y;
	if (!g->mouse_initialized)
	{
		g->mouse_last_x = x;
		g->mouse_initialized = 1;
		return (0);
	}
	delta_x = x - g->mouse_last_x;
	if (delta_x > 1 || delta_x < -1)
	{
		rotation = delta_x * MOUSE_SENSITIVITY;
		rotate_camera_mouse(g, rotation);
		render_scene_with_bonus(g->mlx, g);
	}
	g->mouse_last_x = x;
	return (0);
}

// Setup básico sin forzar posición del mouse
void	setup_mouse_hooks(t_mlx *mlx, t_g *g)
{
	mlx_hook(mlx->win_ptr, 6, 64, mouse_move, g);
	g->mouse_initialized = 0;
	g->mouse_last_x = -1;
}
