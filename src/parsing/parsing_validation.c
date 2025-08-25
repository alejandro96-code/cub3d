/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 00:06:01 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/26 00:06:51 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Handles different validation error types and exits with appropriate message*/
static void	handle_validation_errors(int result)
{
	if (result == -1)
		error_exit(ERROR_NO_TEXTURE);
	else if (result == -2)
		error_exit(ERROR_SO_TEXTURE);
	else if (result == -3)
		error_exit(ERROR_EA_TEXTURE);
	else if (result == -4)
		error_exit(ERROR_WE_TEXTURE);
	else if (result == -5)
		error_exit(ERROR_CEILING_COLOR);
	else if (result == -6)
		error_exit(ERROR_FLOOR_COLOR);
	else if (result == -7)
		error_exit(ERROR_NO_MAP_LINES);
}

/* Validates that all required textures and colors are set before map */
int	validate_map_start(t_g *g)
{
	if (!g->north_texture || !g->south_texture
		|| !g->east_texture || !g->west_texture
		|| !g->ceiling_color_set || !g->floor_color_set)
		return (-3);
	return (1);
}

/* Handles configuration lines (textures and colors) parsing */
int	handle_config_line(char *line, t_g *g)
{
	if (g->map_started)
		return (-1);
	if (!parse_texture_line(line, g) && !parse_color_line(line, g))
		return (-2);
	return (1);
}

/* Handles map line processing and validation */
int	handle_map_line(char *line, t_g *g, char **map_lines, int *map_count)
{
	if (g->map_finished)
		return (-1);
	if (!g->map_started)
	{
		if (validate_map_start(g) < 0)
			return (-3);
		g->map_started = 1;
	}
	map_lines[*map_count] = ft_strdup(line);
	if (!map_lines[*map_count])
		return (0);
	(*map_count)++;
	return (1);
}

/* Validates complete parsing and creates final map structure */
int	validate_and_create_map(t_g *g, char **map_lines, int map_count)
{
	int	result;

	result = validate_complete_parsing(g, map_lines, map_count);
	if (result < 0)
	{
		cleanup_map_lines(map_lines, map_count);
		free_g(g);
		handle_validation_errors(result);
		return (0);
	}
	if (!create_map(g, map_lines, map_count))
	{
		cleanup_map_lines(map_lines, map_count);
		free_g(g);
		return (0);
	}
	return (1);
}
