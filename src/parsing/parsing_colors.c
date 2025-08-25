/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 00:00:00 by aleja             #+#    #+#             */
/*   Updated: 2025/08/26 00:06:51 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Processes ceiling color configuration line */
static int	process_ceiling_color(char *line, t_g *g)
{
	char	*rgb_str;
	int		result;

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
