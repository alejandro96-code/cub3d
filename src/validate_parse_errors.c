/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_parse_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:34:38 by aleja             #+#    #+#             */
/*   Updated: 2025/08/21 17:33:51 by alejanr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Parsea valores RGB desde una cadena "r,g,b"
int	parse_rgb_values(char *rgb_str, int *color)
{
	char	**values;
	char	*trimmed_str;
	int		r;
	int		g;
	int		b;

	rgb_str = trim_whitespace(rgb_str);
	trimmed_str = ft_strtrim(rgb_str, " \t");
	if (!trimmed_str)
		return (0);
	values = ft_split(trimmed_str, ',');
	free(trimmed_str);
	if (!values || !values[0] || !values[1] || !values[2])
	{
		printf(ERROR_RGB_FORMAT);
		if (values)
			free_string_array(values);
		return (0);
	}
	r = ft_atoi(trim_whitespace(values[0]));
	g = ft_atoi(trim_whitespace(values[1]));
	b = ft_atoi(trim_whitespace(values[2]));
	free_string_array(values);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (printf(ERROR_RGB_VALUES), 0);
	*color = (r << 16) | (g << 8) | b;
	return (1);
}

// Verifica si una línea es de configuración (textura o color)
int	is_config_line(char *line)
{
	line = trim_whitespace(line);
	if (ft_strlen(line) == 0)
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0)
		return (1);
	return (0);
}

// Verifica que todas las configuraciones requeridas estén presentes
int	validate_config_completeness(t_g *g)
{
	if (!g->north_texture)
		return (printf(ERROR_NO_TEXTURE), 0);
	if (!g->south_texture)
		return (printf(ERROR_SO_TEXTURE), 0);
	if (!g->east_texture)
		return (printf(ERROR_EA_TEXTURE), 0);
	if (!g->west_texture)
		return (printf(ERROR_WE_TEXTURE), 0);
	if (!g->ceiling_color_set)
		return (printf(ERROR_CEILING_COLOR), 0);
	if (!g->floor_color_set)
		return (printf(ERROR_FLOOR_COLOR), 0);
	return (1);
}

// Valida que el archivo se pueda abrir
int	validate_file_access(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

// Valida que las líneas del mapa no estén vacías
int	validate_map_lines_count(int map_count)
{
	if (map_count == 0)
		return (printf(ERROR_NO_MAP_LINES), 0);
	return (1);
}

// Función de validación completa del parsing
int	validate_complete_parsing(t_g *g, char **map_lines, int map_count)
{
	if (!validate_config_completeness(g))
	{
		cleanup_map_lines(map_lines, map_count);
		free_g(g);
		return (0);
	}
	if (!validate_map_lines_count(map_count))
	{
		cleanup_map_lines(map_lines, map_count);
		free_g(g);
		return (0);
	}
	return (1);
}

