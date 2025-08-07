/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:18:43 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/07 02:27:05 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_mlx *mlx, t_cub_config *cfg, t_raycast *v)
{
	int	y;

	y = 0;
	while (y < v->draw_start)
	{
		mlx->pixels[y * mlx->width + v->x] = cfg->ceiling_color;
		y++;
	}
	y = v->draw_end;
	while (y < mlx->height)
	{
		mlx->pixels[y * mlx->width + v->x] = cfg->floor_color;
		y++;
	}
}

static t_texture	*get_texture(t_cub_config *cfg, t_raycast *v)
{
	if (v->side == 0 && v->ray_dir_x > 0)
		return (&cfg->textures[0]);
	else if (v->side == 0 && v->ray_dir_x < 0)
		return (&cfg->textures[1]);
	else if (v->side == 1 && v->ray_dir_y > 0)
		return (&cfg->textures[2]);
	else
		return (&cfg->textures[3]);
}

static void	draw_texture_column(t_mlx *mlx, t_texture *tex, t_raycast *v)
{
	double	step;
	double	tex_pos;
	int		y;
	int		color;

	if (!tex || !tex->buffer || tex->width <= 0 || tex->height <= 0)
		return ;
	step = (double)tex->height / v->line_height;
	tex_pos = (v->draw_start - mlx->height / 2.0 + v->line_height / 2.0) * step;
	y = v->draw_start;
	while (y < v->draw_end)
	{
		int	tex_y;

		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		if (v->tex_x >= 0 && v->tex_x < tex->width && tex_y >= 0 && tex_y < tex->height)
		{
			color = tex->buffer[tex_y * tex->width + v->tex_x];
			if (v->side == 1)
				color = (color >> 1) & 0x7F7F7F;
			my_mlx_pixel_put(mlx, v->x, y, color);
		}
		y++;
	}
}

void	draw_wall_textures(t_mlx *mlx, t_cub_config *cfg, t_player *player,
		t_raycast *v)
{
	t_texture	*tex;
	double		wall_x;

	if (v->side == 0)
		wall_x = player->y + v->perp_wall_dist * v->ray_dir_y;
	else
		wall_x = player->x + v->perp_wall_dist * v->ray_dir_x;
	wall_x -= floor(wall_x);
	tex = get_texture(cfg, v);
	if (!tex || tex->width <= 0)
		return ;
	v->tex_x = (int)(wall_x * tex->width);
	if ((v->side == 0 && v->ray_dir_x > 0) || (v->side == 1 && v->ray_dir_y < 0))
		v->tex_x = tex->width - v->tex_x - 1;
	draw_texture_column(mlx, tex, v);
}
