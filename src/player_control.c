/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:57:21 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/06 12:02:38 by ybahri           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

void	move_player(int keycode, t_game *game)
{
	double	new_y;
	double	new_x;
	char	**map;

	new_x = game->player->x;
	new_y = game->player->y;
	map = game->cfg->map;

	if (keycode == KEY_W)
	{
		new_x += game->player->dir_x * game->player->move_speed;
		new_y += game->player->dir_y * game->player->move_speed;
	}
	else if (keycode == KEY_S)
	{
		new_x -= game->player->dir_x * game->player->move_speed;
		new_y -= game->player->dir_y * game->player->move_speed;
	}
	else if (keycode == KEY_A)
	{
		new_x -= game->player->dir_x * game->player->move_speed;
		new_y -= game->player->dir_y * game->player->move_speed;
	}
	else if (keycode == KEY_D)
	{
		new_x += game->player->dir_x * game->player->move_speed;
		new_y += game->player->dir_y * game->player->move_speed;
	}

	//comprueba colisiones
	if (map[(int)game->player->y][(int)new_x] == '0')
		game->player->x = new_x;
	if (map[(int)new_y][(int)game->player->x] == '0')
		game->player->y = new_y;
}

void rotate_view(int keycode, t_game *game)
{
	double old_dir_x;
	double old_plane_x;
	double angle;

	old_dir_x = game->player->dir_x;
	old_plane_x = game->player->plane_x;
	angle = (keycode == KEY_LEFT)
		? game->player->rot_speed
		: -game->player->rot_speed;

//Rotación del vector de dirección
	game->player->dir_x = old_dir_x * cos(angle)
	- game->player->dir_y * sin(angle);
	game->player->dir_y = old_dir_x * sin(angle)
	+ game->player->dir_y * cos(angle);

//Rotación del plano de cámara
	game->player->plane_x = old_plane_x * cos(angle)
	- game->player->plane_y * sin(angle);
	game->player->plane_y = old_plane_x * sin(angle) 
	+ game->player->plane_y * cos(angle);
}
