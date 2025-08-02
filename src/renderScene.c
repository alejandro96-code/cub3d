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

void	render_scene(t_mlx *mlx, t_cub_config *cfg, t_player *player)
{
	int				x;
	t_raycast_vars	v;

	x = 0;
	while (x < mlx->width)
	{
		v.x = x;
		calculate_ray_direction(player, mlx, &v);
		calculate_step_and_side_dist(player, &v);
		v.side = raycast_dda(cfg, &v);
		calculate_perp_wall_and_lineheight(mlx, player, &v);
		calculate_draw_limits(mlx, &v);
		v.rayinfo.ray_dir_x = v.ray_dir_x;
		v.rayinfo.ray_dir_y = v.ray_dir_y;
		v.paintinfo.mlx = mlx;
		v.paintinfo.x = v.x;
		v.paintinfo.draw_start = v.draw_start;
		v.paintinfo.draw_end = v.draw_end;
		v.paintinfo.side = v.side;
		draw_column_colors(&v.paintinfo, &v.rayinfo);
		x++;
	}
	bonus_minimap(mlx, cfg);
}
