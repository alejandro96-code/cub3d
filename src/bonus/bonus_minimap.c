/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:26:52 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/26 01:18:55 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Draw a square on the minimap */
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

/* Render a fixed minimap in the top-left corner */
void	bonus_minimap(t_mlx *mlx, t_g *g)
{
	int		px;
	int		py;
	char	c;
	int		y;
	int		x;

	y = 0;
	while (y < g->map_height)
	{
		x = 0;
		while (x < g->map_width)
		{
			px = MINIMAP_MARGIN + x * MINIMAP_CELL_SIZE;
			py = MINIMAP_MARGIN + y * MINIMAP_CELL_SIZE;
			c = g->map[y][x];
			if (c == '1')
				draw_square(mlx, px, py, MINIMAP_WALL_COLOR);
			else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				draw_square(mlx, px, py, MINIMAP_FLOOR_COLOR);
			x++;
		}
		y++;
	}
}
