/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:34:38 by aleja             #+#    #+#             */
/*   Updated: 2025/09/16 09:07:15 by alejanr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Calcula la dirección del rayo y la posición de la cámara
para cada columna de la pantalla */
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

/* Calcula los pasos (step_x y step_y) que el rayo debe dar en el mapa
(en qué dirección moverse en el eje X o Y).
También calcula la distancia inicial (side_dist_x y side_dist_y)
hasta la primera línea de cuadrícula que el rayo cruza.*/

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

/* Implementa el algoritmo DDA (Digital Differential Analyzer),
que avanza el rayo paso a paso en el mapa hasta que golpea una pared.
Determina si el rayo se mueve más rápido en el eje X o Y y actualiza
las coordenadas del mapa (map_x, map_y) hasta encontrar un obstáculo.*/
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
			|| g->map_y >= g->map_height || g->map[g->map_y][g->map_x] != '0')
			hit = 1;
	}
	return (g->side);
}

/* Calcula la distancia perpendicular desde el jugador
hasta la pared que el rayo golpeó.
Usa esta distancia para determinar la altura de la línea
que se debe dibujar en la pantalla para representar esa pared. */
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

/* Calcula los límites superior e inferior de la línea que
se dibujará en la pantalla para esa pared.
Esto asegura que las paredes se dibujen correctamente en
perspectiva, ajustando su altura según la distancia. */
void	calculate_draw_limits(t_mlx *mlx, t_g *g)
{
	g->draw_start = -g->line_height / 2 + mlx->height / 2;
	if (g->draw_start < 0)
		g->draw_start = 0;
	g->draw_end = g->line_height / 2 + mlx->height / 2;
	if (g->draw_end >= mlx->height)
		g->draw_end = mlx->height - 1;
}
