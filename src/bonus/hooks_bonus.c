/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:27:11 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/22 15:27:14 by ybahri           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

void	setup_hooks(t_g *g)
{
	mlx_hook(g->mlx->win_ptr, KEYPRESS, KEYPRESSMASK, key_press, g);
	mlx_hook(g->mlx->win_ptr, 33, 1L << 17, close_window_hook, g);
	setup_mouse_hooks(g->mlx, g);
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
	render_scene_with_bonus(g->mlx, g);
	return (0);
}

int	close_window_hook(t_g *g)
{
	destroy_window(g->mlx);
	free_g(g);
	exit(0);
}
