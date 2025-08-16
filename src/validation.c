/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:45:00 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/16 13:23:24 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Comprueba que exista exactamente un jugador en el mapa (N, S, E, W)
int	has_player(t_g *g)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	y = 0;
	count = 0;
	while (y < g->map_height)
	{
		x = 0;
		while (x < g->map_width)
		{
			if (g->map[y][x] == 'N' || g->map[y][x] == 'S'
				|| g->map[y][x] == 'E' || g->map[y][x] == 'W')
				count++;
			x++;
		}
		y++;
	}
	return (count == 1);
}

// Comprueba si hay alguna línea vacía en el mapa
int	has_empty_line(t_g *g)
{
	int	y;

	y = 0;
	while (y < g->map_height)
	{
		if (!g->map[y] || g->map[y][0] == '\0')
			return (1);
		y++;
	}
	return (0);
}

// Comprueba que todos los caracteres del mapa sean válidos (0,1,N,S,E,W)
int	has_only_valid_chars(t_g *g)
{
	int		x;
	int		y;
	char	c;

	x = 0;
	y = 0;
	while (y < g->map_height)
	{
		x = 0;
		while (x < g->map_width)
		{
			c = g->map[y][x];
			if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E'
				&& c != 'W' && c != '\0')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

// Verifica que el mapa esté completamente cerrado por '1'
int	is_map_closed(t_g *g)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < g->map_width)
	{
		if (g->map[0][x] != '1' && g->map[0][x] != '\0')
			return (0);
		if (g->map[g->map_height - 1][x] != '1'
			&& g->map[g->map_height - 1][x] != '\0')
			return (0);
		x++;
	}
	while (y < g->map_height)
	{
		if (g->map[y][0] != '1')
			return (0);
		if (g->map[y][g->map_width - 1] != '1'
			&& g->map[y][g->map_width - 1] != '\0')
			return (0);
		y++;
	}
	return (1);
}
