/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderScene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/07 02:43:53 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_framebuffer(t_mlx *mlx)
{
	int	x;

	x = 0;
	while (x < mlx->width * mlx->height)
		mlx->pixels[x++] = 0;
}

static void	render_column(t_mlx *mlx, t_cub_config *cfg, t_player *player,
		t_raycast *v)
{
	calculate_ray_direction(player, mlx, v);
	calculate_step_and_side_dist(player, v);
	v->side = raycast_dda(cfg, v);
	calculate_perp_wall_and_lineheight(mlx, player, v);
	calculate_draw_limits(mlx, v);
	draw_floor_ceiling(mlx, cfg, v);
	draw_wall_textures(mlx, cfg, player, v);
}

void	render_scene(t_mlx *mlx, t_cub_config *cfg, t_player *player)
{
	int			x;
	t_raycast	v;

	clear_framebuffer(mlx);
	x = 0;
	while (x < mlx->width)
	{
		v.x = x;
		render_column(mlx, cfg, player, &v);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	bonus_minimap(mlx, cfg);
}
