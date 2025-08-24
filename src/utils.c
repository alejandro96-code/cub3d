/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:34:38 by aleja             #+#    #+#             */
/*   Updated: 2025/08/24 23:04:03 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_g *g)
{
	char	*dst;
	t_mlx	*mlx;

	mlx = g->mlx;
	if (!mlx || !mlx->pixels)
		return ;
	if (g->x < 0 || g->x >= mlx->width || g->current_pixel_y < 0 || g->current_pixel_y >= mlx->height)
		return ;
	dst = (char *)mlx->pixels + (g->current_pixel_y * mlx->line_len) + (g->x * (mlx->bpp / 8));
	*(unsigned int *)dst = g->current_pixel_color;
}

void	error_exit(const char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
	}
	exit(1);
}