/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 00:00:00 by aleja             #+#    #+#             */
/*   Updated: 2025/09/12 17:29:31 by alejanr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Processes ceiling color configuration line */
static int	process_ceiling_color(char *line, t_g *g)
{
	char	*rgb_str;
	int		result;

	if (g->ceiling_color_set)
		return (-1);
	rgb_str = trim_whitespace(line + 2);
	result = parse_rgb_values(rgb_str, &g->ceiling_color);
	if (result == 1)
		g->ceiling_color_set = 1;
	return (result);
}

/* Processes floor color configuration line */
static int	process_floor_color(char *line, t_g *g)
{
	char	*rgb_str;
	int		result;

	if (g->floor_color_set)
		return (-1);
	rgb_str = trim_whitespace(line + 2);
	result = parse_rgb_values(rgb_str, &g->floor_color);
	if (result == 1)
		g->floor_color_set = 1;
	return (result);
}

/* Parses color configuration lines (C for ceiling, F for floor) */
int	parse_color_line(char *line, t_g *g)
{
	line = trim_whitespace(line);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (process_ceiling_color(line, g));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (process_floor_color(line, g));
	return (0);
}
