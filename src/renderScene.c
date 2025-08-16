/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderScene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/16 13:23:24 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_column(t_mlx *mlx, t_g *g)
{
	calculate_ray_direction(g, mlx);
	calculate_step_and_side_dist(g);
	g->side = raycast_dda(g);
	calculate_perp_wall_and_lineheight(mlx, g);
	calculate_draw_limits(mlx, g);
	draw_floor_ceiling(mlx, g);
	draw_wall_textures(mlx, g);
}

void	render_scene(t_mlx *mlx, t_g *g)
{
	int			x;

	x = 0;
	while (x < mlx->width)
	{
		g->x = x;
		render_column(mlx, g);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
// #ifdef BONUS
// 	bonus_minimap(mlx, g);
// #endif
}
