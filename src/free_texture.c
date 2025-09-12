/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:18:43 by ybahri            #+#    #+#             */
/*   Updated: 2025/09/12 17:30:02 by alejanr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_g *g)
{
	int	i;

	if (!g || !g->mlx || !g->mlx->mlx_ptr)
		return ;
	i = 0;
	while (i < 4)
	{
		if (g->tex_img_ptr[i])
			mlx_destroy_image(g->mlx->mlx_ptr, g->tex_img_ptr[i]);
		i++;
	}
}
