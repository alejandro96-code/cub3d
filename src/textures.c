/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:18:18 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/07 02:18:20 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	load_one(char *path, t_mlx *mlx)
{
	t_texture	tex;
	int			bpp;
	int			line_len;
	int			endian;

	tex.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &tex.width,
			&tex.height);
	if (!tex.img_ptr)
	{
		printf("Error: No se pudo cargar la textura: %s\n", path);
		exit(1);
	}
	tex.buffer = (int *)mlx_get_data_addr(tex.img_ptr, &bpp, &line_len,
			&endian);
	if (!tex.buffer)
	{
		printf("Error: No se pudo obtener el buffer de la textura: %s\n", path);
		exit(1);
	}
	return (tex);
}

void	load_textures(t_mlx *mlx, t_cub_config *cfg)
{
	cfg->textures[IDX_NO] = load_one("src/textures/north.xpm", mlx);
	cfg->textures[IDX_SO] = load_one("src/textures/south.xpm", mlx);
	cfg->textures[IDX_EA] = load_one("src/textures/east.xpm", mlx);
	cfg->textures[IDX_WE] = load_one("src/textures/west.xpm", mlx);
}
