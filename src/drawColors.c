/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawColors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/16 13:23:24 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Pinta la columna de colores (techo, pared, suelo) para una columna x
void	draw_ceiling_wall_floor(t_mlx *mlx, t_g *g)
{
	int	y;

	y = 0;
	while (y < g->draw_start)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, g->x, y, g->ceiling_color);
		y++;
	}
	while (y <= g->draw_end)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, g->x, y, g->color);
		y++;
	}
	while (y < mlx->height)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, g->x, y, g->floor_color);
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
void	draw_column_colors(t_mlx *mlx, t_g *g)
{
	g->color = get_wall_color(g->side, g->ray_dir_x, g->ray_dir_y);
	draw_ceiling_wall_floor(mlx, g);
}
