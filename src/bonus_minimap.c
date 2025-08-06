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

// Dibuja un cuadrado en el minimapa
static void	draw_square(void *mlx_ptr, void *win_ptr, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_CELL_SIZE)
	{
		j = 0;
		while (j < MINIMAP_CELL_SIZE)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

// Renderiza un minimapa fijo en la esquina superior izquierda
void	bonus_minimap(t_mlx *mlx, t_cub_config *cfg)
{
	int		px;
	int		py;
	char	c;
	int		y;
	int		x;

	y = 0;
	while (y < cfg->map_height)
	{
		x = 0;
		while (x < cfg->map_width)
		{
			px = MINIMAP_MARGIN + x * MINIMAP_CELL_SIZE;
			py = MINIMAP_MARGIN + y * MINIMAP_CELL_SIZE;
			c = cfg->map[y][x];
			if (c == '1')
				draw_square(mlx->mlx_ptr, mlx->win_ptr, px, py,
					MINIMAP_WALL_COLOR);
			else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				draw_square(mlx->mlx_ptr, mlx->win_ptr, px, py,
					MINIMAP_FLOOR_COLOR);
			x++;
		}
		y++;
	}
}