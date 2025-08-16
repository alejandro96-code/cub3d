/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:18:43 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/16 13:23:24 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_mlx *mlx, t_g *g)
{
	int	y;

	if (!mlx || !mlx->pixels || !g)
		return ;
	y = 0;
	while (y < g->draw_start && y >= 0 && y < mlx->height)
	{
		if (g->x >= 0 && g->x < mlx->width)
			mlx->pixels[y * mlx->width + g->x] = g->ceiling_color;
		y++;
	}
	y = g->draw_end;
	while (y < mlx->height && y >= 0)
	{
		if (g->x >= 0 && g->x < mlx->width)
			mlx->pixels[y * mlx->width + g->x] = g->floor_color;
		y++;
	}
}

static int	get_texture_idx(t_g *g)
{
	if (g->side == 0 && g->ray_dir_x > 0)
		return (IDX_EA);
	else if (g->side == 0 && g->ray_dir_x < 0)
		return (IDX_WE);
	else if (g->side == 1 && g->ray_dir_y > 0)
		return (IDX_SO);
	else
		return (IDX_NO);
}

static void	draw_texture_column(t_mlx *mlx, int tex_idx, t_g *g)
{
	double	step;
	double	tex_pos;
	int		y;
	int		color;
	int		tex_y;

	if (!g->tex_buffer[tex_idx] || g->tex_width[tex_idx] <= 0
		|| g->tex_height[tex_idx] <= 0)
		return ;
	step = (double)g->tex_height[tex_idx] / g->line_height;
	tex_pos = (g->draw_start - mlx->height / 2.0 + g->line_height / 2.0)
		* step;
	y = g->draw_start;
	while (y < g->draw_end)
	{
		tex_y = (int)tex_pos & (g->tex_height[tex_idx] - 1);
		tex_pos += step;
		if (g->tex_x >= 0 && g->tex_x < g->tex_width[tex_idx]
			&& tex_y >= 0 && tex_y < g->tex_height[tex_idx])
		{
			color = g->tex_buffer[tex_idx][tex_y * g->tex_width[tex_idx]
				+ g->tex_x];
			if (g->side == 1)
				color = (color >> 1) & 0x7F7F7F;
			my_mlx_pixel_put(mlx, g->x, y, color);
		}
		y++;
	}
}

void	draw_wall_textures(t_mlx *mlx, t_g *g)
{
	int		tex_idx;
	double	wall_x;

	if (g->side == 0)
		wall_x = g->player_y + g->perp_wall_dist * g->ray_dir_y;
	else
		wall_x = g->player_x + g->perp_wall_dist * g->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_idx = get_texture_idx(g);
	if (g->tex_width[tex_idx] <= 0)
		return ;
	g->tex_x = (int)(wall_x * g->tex_width[tex_idx]);
	if ((g->side == 0 && g->ray_dir_x > 0) || (g->side == 1
			&& g->ray_dir_y < 0))
		g->tex_x = g->tex_width[tex_idx] - g->tex_x - 1;
	draw_texture_column(mlx, tex_idx, g);
}
