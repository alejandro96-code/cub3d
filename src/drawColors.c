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

// Pinta la columna de colores (techo, pared, suelo) para una columna x
void	draw_ceiling_wall_floor(t_mlx *mlx, t_cub_config *cfg, t_raycast *v)
{
	int	y;

	y = 0;
	while (y < v->draw_start)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, v->x, y, cfg->ceiling_color);
		y++;
	}
	while (y <= v->draw_end)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, v->x, y, v->color);
		y++;
	}
	while (y < mlx->height)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, v->x, y, cfg->floor_color);
		y++;
	}
}

/* Pinta los muros
   Este - naranja
   Oeste - turquesa
   Sur - violeta
   Norte- dorado
*/
int	get_wall_color(int side, double ray_dir_x, double ray_dir_y)
{
	if (side == 0 && ray_dir_x > 0)
		return (0xFF8000);
	else if (side == 0 && ray_dir_x < 0)
		return (0x00FFB3);
	else if (side == 1 && ray_dir_y > 0)
		return (0x8A2BE2);
	else
		return (0xFFD700);
}

// Llama a las funciones anteriores
void	draw_column_colors(t_mlx *mlx, t_cub_config *cfg, t_raycast *v)
{
	v->color = get_wall_color(v->side, v->ray_dir_x, v->ray_dir_y);
	draw_ceiling_wall_floor(mlx, cfg, v);
}