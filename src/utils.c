/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:34:38 by aleja             #+#    #+#             */
/*   Updated: 2025/08/16 12:53:44 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (!mlx || !mlx->pixels)
		return ;
	if (x < 0 || x >= mlx->width || y < 0 || y >= mlx->height)
		return ;
	dst = (char *)mlx->pixels + (y * mlx->line_len) + (x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	free_cub_config(t_cub_config *cfg)
{
	int	i;

	if (cfg->map)
	{
		i = 0;
		while (i < cfg->map_height)
		{
			free(cfg->map[i]);
			i++;
		}
		free(cfg->map);
	}
	free(cfg);
}
