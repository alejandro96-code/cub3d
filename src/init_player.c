/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/05 22:17:29 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Inicializa la dirección y el plano del jugador para norte o sur
void	set_player_direction_ns(t_player *player, char c)
{
	if (c == PLAYER_N)
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (c == PLAYER_S)
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
}

// Inicializa la dirección y el plano del jugador para este u oeste
void	set_player_direction_ew(t_player *player, char c)
{
	if (c == PLAYER_E)
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (c == PLAYER_W)
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

// Llama a la función adecuada según el carácter
void	set_player_direction(t_player *player, char c)
{
	if (c == PLAYER_N || c == PLAYER_S)
		set_player_direction_ns(player, c);
	else if (c == PLAYER_E || c == PLAYER_W)
		set_player_direction_ew(player, c);
}

/*
	Inicializa la estructura del jugador según el
	primer carácter de jugador encontrado en el mapa
*/
void	init_player_from_map(t_player *player, t_cub_config *cfg)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < cfg->map_height)
	{
		x = 0;
		while (x < cfg->map_width)
		{
			c = cfg->map[y][x];
			if (c == PLAYER_N || c == PLAYER_S || c == PLAYER_E
				|| c == PLAYER_W)
			{
				player->x = x + 0.5;
				player->y = y + 0.5;
				set_player_direction(player, c);
				player->rot_speed = 0.05;
				player->move_speed = 0.1;
				return ;
			}
			x++;
		}
		y++;
	}
}
