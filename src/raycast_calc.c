/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/07/29 16:38:20 by alejanr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calcula la dirección del rayo y la posición de la cámara para una columna x
void	calculate_ray_direction(const t_player *player, t_mlx *mlx,
		t_raycast *v)
{
	v->camera_x = 2 * v->x / (double)mlx->width - 1;
	v->ray_dir_x = player->dir_x + player->plane_x * v->camera_x;
	v->ray_dir_y = player->dir_y + player->plane_y * v->camera_x;
	v->map_x = (int)player->x;
	v->map_y = (int)player->y;
	v->delta_dist_x = fabs(1 / v->ray_dir_x);
	v->delta_dist_y = fabs(1 / v->ray_dir_y);
}

/*
	Calcula el paso y la distancia inicial a la
	siguiente línea de grid para el algoritmo DDA
*/
void	calculate_step_and_side_dist(const t_player *player, t_raycast *v)
{
	if (v->ray_dir_x < 0)
	{
		v->step_x = -1;
		v->side_dist_x = (player->x - v->map_x) * v->delta_dist_x;
	}
	else
	{
		v->step_x = 1;
		v->side_dist_x = (v->map_x + 1.0 - player->x) * v->delta_dist_x;
	}
	if (v->ray_dir_y < 0)
	{
		v->step_y = -1;
		v->side_dist_y = (player->y - v->map_y) * v->delta_dist_y;
	}
	else
	{
		v->step_y = 1;
		v->side_dist_y = (v->map_y + 1.0 - player->y) * v->delta_dist_y;
	}
}

/*
	Realiza el algoritmo DDA para avanzar el rayo hasta chocar con una pared
	Devuelve el lado impactado y modifica map_x/map_y
*/
int	raycast_dda(const t_cub_config *cfg, t_raycast *v)
{
	int	hit;

	hit = 0;
	v->side = 0;
	while (!hit)
	{
		if (v->side_dist_x < v->side_dist_y)
		{
			v->side_dist_x += v->delta_dist_x;
			v->map_x += v->step_x;
			v->side = 0;
		}
		else
		{
			v->side_dist_y += v->delta_dist_y;
			v->map_y += v->step_y;
			v->side = 1;
		}
		if (cfg->map[v->map_y][v->map_x] == '1')
			hit = 1;
	}
	return (v->side);
}

/*
	Calcula la distancia perpendicular a la pared
	y la altura de la línea a dibujar
*/

void	calculate_perp_wall_and_lineheight(t_mlx *mlx, t_player *player,
		t_raycast *v)
{
	if (v->side == 0)
		v->perp_wall_dist = (v->map_x - player->x + (1 - v->step_x) / 2)
			/ v->ray_dir_x;
	else
		v->perp_wall_dist = (v->map_y - player->y + (1 - v->step_y) / 2)
			/ v->ray_dir_y;
	v->line_height = (int)(mlx->height / v->perp_wall_dist);
}

// Calcula los límites de dibujo (draw_start, draw_end) para la columna actual
void	calculate_draw_limits(t_mlx *mlx, t_raycast *v)
{
	v->draw_start = -v->line_height / 2 + mlx->height / 2;
	if (v->draw_start < 0)
		v->draw_start = 0;
	v->draw_end = v->line_height / 2 + mlx->height / 2;
	if (v->draw_end >= mlx->height)
		v->draw_end = mlx->height - 1;
}
