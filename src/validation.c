/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:45:00 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/24 21:26:50 by aleja            ###   ########.fr       */
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
	int	x;
	int	only_spaces;

	y = 0;
	while (y < g->map_height)
	{
		if (!g->map[y] || g->map[y][0] == '\0')
			return (1);
		
		// Verificar si la línea contiene solo espacios
		only_spaces = 1;
		x = 0;
		while (g->map[y][x])
		{
			if (g->map[y][x] != ' ')
			{
				only_spaces = 0;
				break;
			}
			x++;
		}
		if (only_spaces && ft_strlen(g->map[y]) > 0)
			return (1);
		
		y++;
	}
	return (0);
}

static int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

// Comprueba que todos los caracteres del mapa sean válidos (0,1,N,S,E,W)
int	has_only_valid_chars(t_g *g)
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
			if (c != '0' && c != '1' && c != ' ' && !is_player_char(c))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static int	cell_is_open(t_g *g, int x, int y)
{
	if (x < 0 || y < 0 || y >= g->map_height || x >= g->map_width)
		return (1);
	if (g->map[y][x] == ' ' || g->map[y][x] == '\0')
		return (1);
	return (0);
}

// Verifica que el mapa esté completamente cerrado por '1'
int	is_map_closed(t_g *g)
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
			if (c == '0' || (c == 'N' || c == 'S' || c == 'E' || c == 'W'))
			{
				if (cell_is_open(g, x + 1, y) || cell_is_open(g, x - 1, y)
					|| cell_is_open(g, x, y + 1) || cell_is_open(g, x, y - 1))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
