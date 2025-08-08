/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:17:59 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/08 13:30:06 by ybahri           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

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
