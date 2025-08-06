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

void	setup_hooks(t_game *game)
{
	mlx_hook(game->mlx->win_ptr, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->mlx->win_ptr, 33, 1L<<17, close_window, game);
	mlx_loop_hook(game->mlx->mlx_ptr, loop_render, game);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		return (close_window(game));
	if (keycode == KEY_W || keycode == KEY_S
		|| keycode == KEY_A || keycode == KEY_D)
		move_player(keycode, game);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		rotate_view(keycode, game);
	return (0);
}

int	loop_render(t_game *game)
{
	mlx_clear_window(game->mlx->mlx_ptr, game->mlx->win_ptr);
	render_scene(game->mlx, game->cfg, game->player);
	return (0);
}
