/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:18:18 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/16 13:23:24 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_one(char *path, t_mlx *mlx, int idx, t_g *g)
{
	int	bpp;
	int	line_len;
	int	endian;

	g->tex_img_ptr[idx] = mlx_xpm_file_to_image(mlx->mlx_ptr, path,
			&g->tex_width[idx], &g->tex_height[idx]);
	if (!g->tex_img_ptr[idx])
	{
		printf("Error: No se pudo cargar la textura: %s\n", path);
		exit(1);
	}
	g->tex_buffer[idx] = (int *)mlx_get_data_addr(g->tex_img_ptr[idx],
			&bpp, &line_len, &endian);
	if (!g->tex_buffer[idx])
	{
		printf("Error: No se pudo obtener el buffer de la textura: %s\n", path);
		exit(1);
	}
}

void	load_textures(t_mlx *mlx, t_g *g)
{
	load_one("src/textures/north.xpm", mlx, IDX_NO, g);
	load_one("src/textures/south.xpm", mlx, IDX_SO, g);
	load_one("src/textures/east.xpm", mlx, IDX_EA, g);
	load_one("src/textures/west.xpm", mlx, IDX_WE, g);
}
