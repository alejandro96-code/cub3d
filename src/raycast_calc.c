/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:34:38 by aleja             #+#    #+#             */
/*   Updated: 2025/08/26 01:11:19 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Calculate ray direction and camera position for column x */
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

/* Calculate step and initial distance to next grid line for DDA algorithm */
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

/* Perform DDA algorithm to advance ray until hitting a wall */
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
		if (g->map_x < 0 || g->map_x >= g->map_width
			|| g->map_y < 0 || g->map_y >= g->map_height
			|| g->map[g->map_y][g->map_x] != '0')
			hit = 1;
	}
	return (g->side);
}

/* Calculate perpendicular wall distance and line height */
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

/* Calculate drawing limits for wall column */
void	calculate_draw_limits(t_mlx *mlx, t_g *g)
{
	g->draw_start = -g->line_height / 2 + mlx->height / 2;
	if (g->draw_start < 0)
		g->draw_start = 0;
	g->draw_end = g->line_height / 2 + mlx->height / 2;
	if (g->draw_end >= mlx->height)
		g->draw_end = mlx->height - 1;
}
