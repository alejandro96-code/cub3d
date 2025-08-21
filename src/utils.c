/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:34:38 by aleja             #+#    #+#             */
/*   Updated: 2025/08/21 17:10:18 by alejanr2         ###   ########.fr       */
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
