/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/08 10:57:59 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Dibuja un cuadrado en el minimapa
static void	draw_square(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_CELL_SIZE)
	{
		j = 0;
		while (j < MINIMAP_CELL_SIZE)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x + i, y + j, color);
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
				draw_square(mlx, px, py, MINIMAP_WALL_COLOR);
			else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				draw_square(mlx, px, py, MINIMAP_FLOOR_COLOR);
			x++;
		}
		y++;
	}
}
