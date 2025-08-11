/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:35:26 by aleja             #+#    #+#             */
/*   Updated: 2025/08/11 19:39:47 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_hooks(t_mlx *mlx, t_cub_config *cfg, t_player *player,
		t_hook_data *hook_data)
{
	hook_data->mlx = mlx;
	hook_data->cfg = cfg;
	hook_data->player = player;
	mlx_hook(mlx->win_ptr, KEYPRESS, KEYPRESSMASK, key_press, hook_data);
	mlx_hook(mlx->win_ptr, 33, 1L << 17, close_window_hook, hook_data);
}

int	key_press(int keycode, t_hook_data *data)
{
	if (keycode == KEY_ESC)
		return (close_window_hook(data));
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
		|| keycode == KEY_D)
		move_player(keycode, data->cfg, data->player);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		rotate_view(keycode, data->player);
	render_scene(data->mlx, data->cfg, data->player);
	return (0);
}

int	close_window_hook(t_hook_data *data)
{
	destroy_window(data->mlx);
	free_cub_config(data->cfg);
	exit(0);
}
