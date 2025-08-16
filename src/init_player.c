/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/16 13:36:52 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Inicializa la dirección y el plano del jugador para norte o sur
void	set_player_direction_ns(t_g *g, char c)
{
	if (c == PLAYER_N)
	{
		g->dir_x = 0;
		g->dir_y = -1;
		g->plane_x = 0.66;
		g->plane_y = 0;
	}
	else if (c == PLAYER_S)
	{
		g->dir_x = 0;
		g->dir_y = 1;
		g->plane_x = -0.66;
		g->plane_y = 0;
	}
}

// Inicializa la dirección y el plano del jugador para este u oeste
void	set_player_direction_ew(t_g *g, char c)
{
	if (c == PLAYER_E)
	{
		g->dir_x = 1;
		g->dir_y = 0;
		g->plane_x = 0;
		g->plane_y = 0.66;
	}
	else if (c == PLAYER_W)
	{
		g->dir_x = -1;
		g->dir_y = 0;
		g->plane_x = 0;
		g->plane_y = -0.66;
	}
}

// Llama a la función adecuada según el carácter
void	set_player_direction(t_g *g, char c)
{
	if (c == PLAYER_N || c == PLAYER_S)
		set_player_direction_ns(g, c);
	else if (c == PLAYER_E || c == PLAYER_W)
		set_player_direction_ew(g, c);
}

/*
	Inicializa la estructura del jugador según el
	primer carácter de jugador encontrado en el mapa
*/
void	init_player_from_map(t_g *g)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < g->map_height)
	{
		x = 0;
		while (x < g->map_width)
		{
			c = g->map[y][x];
			if (c == PLAYER_N || c == PLAYER_S || c == PLAYER_E
				|| c == PLAYER_W)
			{
				g->player_x = x + 0.5;
				g->player_y = y + 0.5;
				set_player_direction(g, c);
				g->mouse_initialized = 0;
				g->mouse_last_x = -1;
				return ;
			}
			x++;
		}
		y++;
	}
}
