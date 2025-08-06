/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 21:40:43 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/06 12:01:51 by ybahri           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

// Variable global para los datos del hook
static t_hook_data	g_hook_data;

void	setup_hooks(t_mlx *mlx, t_cub_config *cfg, t_player *player)
{
	// Configurar datos globales
	g_hook_data.mlx = mlx;
	g_hook_data.cfg = cfg;
	g_hook_data.player = player;
	
	// Configurar hooks de eventos
	mlx_hook(mlx->win_ptr, KeyPress, KeyPressMask, key_press, &g_hook_data);
	mlx_hook(mlx->win_ptr, 33, 1L<<17, close_window_hook, &g_hook_data);
}

int	key_press(int keycode, t_hook_data *data)
{
	if (keycode == KEY_ESC)
		return (close_window_hook(data));
	if (keycode == KEY_W || keycode == KEY_S
		|| keycode == KEY_A || keycode == KEY_D)
		move_player(keycode, data->cfg, data->player);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		rotate_view(keycode, data->player);
	
	// Re-renderizar después del movimiento
	render_scene(data->mlx, data->cfg, data->player);
	return (0);
}

int	close_window_hook(t_hook_data *data)
{
	destroy_window(data->mlx);
	free_cub_config(data->cfg);
	exit(0);
}
