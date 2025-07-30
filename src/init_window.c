/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/07/29 16:38:20 by alejanr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlx *init_window(const t_cub_config *cfg)
{
    t_mlx *mlx = malloc(sizeof(t_mlx));
    if (!mlx)
        return NULL;
    mlx->width = cfg->map_width * 64;
    mlx->height = cfg->map_height * 64;
    mlx->mlx_ptr = mlx_init();
    if (!mlx->mlx_ptr) {
        free(mlx);
        return NULL;
    }
    mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->width, mlx->height, "cub3D");
    if (!mlx->win_ptr) {
        free(mlx);
        return NULL;
    }
    return mlx;
}

void destroy_window(t_mlx *mlx)
{
    if (!mlx) return;
    if (mlx->win_ptr && mlx->mlx_ptr)
        mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
    free(mlx);
}
