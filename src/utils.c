/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:34:38 by aleja             #+#    #+#             */
/*   Updated: 2025/08/21 09:27:20 by alejanr2         ###   ########.fr       */
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

void	free_g(t_g *g)
{
	int	i;

	if (!g)
		return;
	if (g->map)
	{
		i = 0;
		while (i < g->map_height)
		{
			free(g->map[i]);
			i++;
		}
		free(g->map);
	}
	if (g->north_texture)
		free(g->north_texture);
	if (g->south_texture)
		free(g->south_texture);
	if (g->east_texture)
		free(g->east_texture);
	if (g->west_texture)
		free(g->west_texture);
	free(g);
}
