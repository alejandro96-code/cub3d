/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 00:51:22 by ybahri            #+#    #+#             */
/*   Updated: 2025/09/12 17:26:49 by alejanr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_hooks(t_g *g)
{
	mlx_hook(g->mlx->win_ptr, KEYPRESS, KEYPRESSMASK, key_press, g);
	mlx_hook(g->mlx->win_ptr, 33, 1L << 17, close_window_hook, g);
}

int	key_press(int keycode, t_g *g)
{
	if (keycode == KEY_ESC)
		return (close_window_hook(g));
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
		|| keycode == KEY_D)
		move_player(keycode, g);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		rotate_view(keycode, g);
	render_scene(g->mlx, g);
	return (0);
}

int	close_window_hook(t_g *g)
{
	free_textures(g);
	destroy_window(g->mlx);
	free_g(g);
	exit(0);
}
