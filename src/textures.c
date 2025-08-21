/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:18:18 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/22 01:07:22 by ybahri           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

static void	load_one(char *path, t_mlx *mlx, int idx, t_g *g)
{
	int	bpp;
	int	line_len;
	int	endian;

	g->tex_img_ptr[idx] = mlx_xpm_file_to_image(mlx->mlx_ptr, path,
			&g->tex_width[idx], &g->tex_height[idx]);
	if (!g->tex_img_ptr[idx])
		error_exit(ERROR_TEXTURE_LOAD);
	g->tex_buffer[idx] = (int *)mlx_get_data_addr(g->tex_img_ptr[idx],
			&bpp, &line_len, &endian);
	if (!g->tex_buffer[idx])
		error_exit(ERROR_TEXTURE_BUFFER);
}

void	load_textures(t_mlx *mlx, t_g *g)
{
	if (!g->north_texture || !g->south_texture || !g->east_texture || !g->west_texture)
		error_exit(ERROR_MISSING_TEXTURES);
	load_one(g->north_texture, mlx, IDX_NO, g);
	load_one(g->south_texture, mlx, IDX_SO, g);
	load_one(g->east_texture, mlx, IDX_EA, g);
	load_one(g->west_texture, mlx, IDX_WE, g);
}
