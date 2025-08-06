/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/06 11:54:32 by ybahri           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

// Función que se ejecuta cuando se cierra la ventana
int	close_window_mlx(t_mlx *mlx)
{
	destroy_window(mlx);
	exit(0);
}

t_mlx	*init_window(const t_cub_config *cfg)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->width = cfg->map_width * 64;
	mlx->height = cfg->map_height * 64;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
	{
		free(mlx);
		return (NULL);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->width, mlx->height,
			"cub3D");
	if (!mlx->win_ptr)
	{
		free(mlx);
		return (NULL);
	}
	mlx_hook(mlx->win_ptr, 33, 1L << 17, close_window_mlx, mlx);
	return (mlx);
}

void	destroy_window(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (mlx->win_ptr && mlx->mlx_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	free(mlx);
}

int	close_window(t_game *game)
{
    if (game->mlx)
        destroy_window(game->mlx);
    if (game->cfg)
        free_cub_config(game->cfg);
    if (game->player)
        free(game->player);
    free(game);
    exit(EXIT_SUCCESS);
    return (0);
}
