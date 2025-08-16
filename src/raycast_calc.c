/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/16 13:23:26 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calcula la dirección del rayo y la posición de la cámara para una columna x
void	calculate_ray_direction(t_g *g, t_mlx *mlx)
{
	g->camera_x = 2 * g->x / (double)mlx->width - 1;
	g->ray_dir_x = g->dir_x + g->plane_x * g->camera_x;
	g->ray_dir_y = g->dir_y + g->plane_y * g->camera_x;
	g->map_x = (int)g->player_x;
	g->map_y = (int)g->player_y;
	g->delta_dist_x = fabs(1 / g->ray_dir_x);
	g->delta_dist_y = fabs(1 / g->ray_dir_y);
}

/*
	Calcula el paso y la distancia inicial a la
	siguiente línea de grid para el algoritmo DDA
*/
void	calculate_step_and_side_dist(t_g *g)
{
	if (g->ray_dir_x < 0)
	{
		g->step_x = -1;
		g->side_dist_x = (g->player_x - g->map_x) * g->delta_dist_x;
	}
	else
	{
		g->step_x = 1;
		g->side_dist_x = (g->map_x + 1.0 - g->player_x) * g->delta_dist_x;
	}
	if (g->ray_dir_y < 0)
	{
		g->step_y = -1;
		g->side_dist_y = (g->player_y - g->map_y) * g->delta_dist_y;
	}
	else
	{
		g->step_y = 1;
		g->side_dist_y = (g->map_y + 1.0 - g->player_y) * g->delta_dist_y;
	}
}

/*
	Realiza el algoritmo DDA para avanzar el rayo hasta chocar con una pared
	Devuelve el lado impactado y modifica map_x/map_y
*/
int	raycast_dda(t_g *g)
{
	int	hit;

	hit = 0;
	g->side = 0;
	while (!hit)
	{
		if (g->side_dist_x < g->side_dist_y)
		{
			g->side_dist_x += g->delta_dist_x;
			g->map_x += g->step_x;
			g->side = 0;
		}
		else
		{
			g->side_dist_y += g->delta_dist_y;
			g->map_y += g->step_y;
			g->side = 1;
		}
		if (g->map_x < 0 || g->map_x >= g->map_width || g->map_y < 0
			|| g->map_y >= g->map_height)
		{
			hit = 1;
		}
		else if (g->map[g->map_y][g->map_x] == '1')
		{
			hit = 1;
		}
	}
	return (g->side);
}

/*
	Calcula la distancia perpendicular a la pared
	y la altura de la línea a dibujar
*/

void	calculate_perp_wall_and_lineheight(t_mlx *mlx, t_g *g)
{
	if (g->side == 0)
		g->perp_wall_dist = (g->map_x - g->player_x + (1 - g->step_x) / 2)
			/ g->ray_dir_x;
	else
		g->perp_wall_dist = (g->map_y - g->player_y + (1 - g->step_y) / 2)
			/ g->ray_dir_y;
	g->line_height = (int)(mlx->height / g->perp_wall_dist);
}

// Calcula los límites de dibujo (draw_start, draw_end) para la columna actual
void	calculate_draw_limits(t_mlx *mlx, t_g *g)
{
	g->draw_start = -g->line_height / 2 + mlx->height / 2;
	if (g->draw_start < 0)
		g->draw_start = 0;
	g->draw_end = g->line_height / 2 + mlx->height / 2;
	if (g->draw_end >= mlx->height)
		g->draw_end = mlx->height - 1;
}
