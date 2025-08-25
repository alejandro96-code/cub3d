/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:45:00 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/26 01:17:36 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Check that exactly one player exists in the map (N, S, E, W) */
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

/* Check if there is any empty line in the map */
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
		only_spaces = 1;
		x = 0;
		while (g->map[y][x])
		{
			if (g->map[y][x] != ' ')
			{
				only_spaces = 0;
				break ;
			}
			x++;
		}
		if (only_spaces && ft_strlen(g->map[y]) > 0)
			return (1);
		y++;
	}
	return (0);
}

/* Check that all map characters are valid (0,1,space,N,S,E,W) */
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
			if (c != '0' && c != '1' && c != ' '
				&& !(c == 'N' || c == 'S' || c == 'E' || c == 'W'))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

/* Check if a cell is open (out of bounds or space) */
static int	cell_is_open(t_g *g, int x, int y)
{
	if (x < 0 || y < 0 || y >= g->map_height || x >= g->map_width)
		return (1);
	if (g->map[y][x] == ' ' || g->map[y][x] == '\0')
		return (1);
	return (0);
}

/* Verify that the map is fully enclosed by '1' */
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
