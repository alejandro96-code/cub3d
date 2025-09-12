/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_parse_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 00:06:29 by ybahri            #+#    #+#             */
/*   Updated: 2025/09/12 17:29:23 by alejanr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Validates that RGB values are within valid range (0-255) */
static int	validate_rgb_range(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return (1);
}

/* Parses RGB string format "r,g,b" and returns array of values */
static char	**parse_rgb_string(char *rgb_str)
{
	char	**values;
	char	*trimmed_str;

	rgb_str = trim_whitespace(rgb_str);
	trimmed_str = ft_strtrim(rgb_str, " \t");
	if (!trimmed_str)
		return (NULL);
	values = ft_split(trimmed_str, ',');
	free(trimmed_str);
	if (!values || !values[0] || !values[1] || !values[2])
	{
		if (values)
			free_string_array(values);
		return (NULL);
	}
	return (values);
}

/* Parses RGB string and converts to hex color value */
int	parse_rgb_values(char *rgb_str, int *color)
{
	char	**values;
	int		r;
	int		g;
	int		b;

	values = parse_rgb_string(rgb_str);
	if (!values)
		return (0);
	r = ft_atoi(trim_whitespace(values[0]));
	g = ft_atoi(trim_whitespace(values[1]));
	b = ft_atoi(trim_whitespace(values[2]));
	free_string_array(values);
	if (!validate_rgb_range(r, g, b))
		return (0);
	*color = (r << 16) | (g << 8) | b;
	return (1);
}

/* Checks if line contains configuration data (textures or colors) */
int	is_config_line(char *line)
{
	line = trim_whitespace(line);
	if (ft_strlen(line) == 0)
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0)
		return (1);
	if (ft_strlen(line) >= 3 && line[2] == ' ' && line[0] >= 'A'
		&& line[0] <= 'Z' && line[1] >= 'A' && line[1] <= 'Z')
		return (1);
	if (ft_strlen(line) >= 2 && line[1] == ' ' && line[0] >= 'A'
		&& line[0] <= 'Z')
		return (1);
	return (0);
}

/* Validates that all required configuration elements are present */
int	validate_config_completeness(t_g *g)
{
	if (!g->north_texture)
		return (-1);
	if (!g->south_texture)
		return (-2);
	if (!g->east_texture)
		return (-3);
	if (!g->west_texture)
		return (-4);
	if (!g->ceiling_color_set)
		return (-5);
	if (!g->floor_color_set)
		return (-6);
	return (1);
}
