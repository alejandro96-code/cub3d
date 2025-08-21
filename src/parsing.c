/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/21 09:27:19 by alejanr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Función auxiliar para eliminar espacios al inicio de una cadena
char	*trim_whitespace(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

// Parsea una línea de textura (NO, SO, WE, EA)
int	parse_texture_line(char *line, t_g *g)
{
	char	*path;
	
	line = trim_whitespace(line);
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		path = trim_whitespace(line + 3);
		g->north_texture = ft_strdup(path);
		return (g->north_texture != NULL);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		path = trim_whitespace(line + 3);
		g->south_texture = ft_strdup(path);
		return (g->south_texture != NULL);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		path = trim_whitespace(line + 3);
		g->west_texture = ft_strdup(path);
		return (g->west_texture != NULL);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		path = trim_whitespace(line + 3);
		g->east_texture = ft_strdup(path);
		return (g->east_texture != NULL);
	}
	return (0);
}

// Parsea valores RGB desde una cadena "r,g,b"
static int	parse_rgb_values(char *rgb_str, int *color)
{
	char	**values;
	int		r, g, b;
	int		i;
	
	values = ft_split(rgb_str, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		if (values)
		{
			i = 0;
			while (values[i])
				free(values[i++]);
			free(values);
		}
		return (0);
	}
	r = ft_atoi(trim_whitespace(values[0]));
	g = ft_atoi(trim_whitespace(values[1]));
	b = ft_atoi(trim_whitespace(values[2]));
	
	// Liberar el array values
	i = 0;
	while (values[i])
		free(values[i++]);
	free(values);
	
	// Verificar que los valores estén en rango válido
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	*color = (r << 16) | (g << 8) | b;
	return (1);
}

// Parsea una línea de color (C para ceiling, F para floor)
int	parse_color_line(char *line, t_g *g)
{
	char	*rgb_str;
	
	line = trim_whitespace(line);
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		rgb_str = trim_whitespace(line + 2);
		return (parse_rgb_values(rgb_str, &g->ceiling_color));
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		rgb_str = trim_whitespace(line + 2);
		return (parse_rgb_values(rgb_str, &g->floor_color));
	}
	return (0);
}

// Verifica si una línea es de configuración (textura o color)
static int	is_config_line(char *line)
{
	line = trim_whitespace(line);
	if (ft_strlen(line) == 0)
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 ||
		ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0)
		return (1);
	return (0);
}

// Crea el mapa en g a partir de las líneas procesadas
static int	create_map(t_g *g, char **lines, int count)
{
	int	l;
	int	i;

	g->map = malloc(count * sizeof(char *));
	if (!g->map)
		return (0);
	g->map_height = count;
	g->map_width = 0;
	i = 0;
	while (i < count)
	{
		g->map[i] = ft_strdup(lines[i]);
		l = ft_strlen(lines[i]);
		if (l > g->map_width)
			g->map_width = l;
		i++;
	}
	return (1);
}

/*
	Función principal: abre el archivo .cub,
	reserva memoria y llama al parser de líneas
*/
t_g	*parse_cub_file(const char *f)
{
	int		fd;
	t_g		*g;
	char	*line;
	char	**map_lines;
	int		map_count;
	int		map_index;
	int		len;

	fd = open(f, O_RDONLY);
	if (fd < 0)
		return (NULL);
	g = ft_calloc(1, sizeof(t_g));
	if (!g)
	{
		close(fd);
		return (NULL);
	}
	
	// Reservar espacio para líneas del mapa (estimación inicial)
	map_lines = malloc(100 * sizeof(char *));
	if (!map_lines)
	{
		close(fd);
		free(g);
		return (NULL);
	}
	map_count = 0;
	map_index = 0;
	
	// Procesar todas las líneas en una sola pasada
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = 0;
			
		if (is_config_line(line))
		{
			if (!parse_texture_line(line, g) && !parse_color_line(line, g))
			{
				printf("Error: Línea de configuración inválida: %s\n", line);
				free(line);
				// Liberar map_lines
				while (map_index > 0)
					free(map_lines[--map_index]);
				free(map_lines);
				free_g(g);
				close(fd);
				return (NULL);
			}
		}
		else if (line[0] != '\0' && (line[0] == ' ' || line[0] == '1' || line[0] == '0'))
		{
			// Es una línea del mapa
			map_lines[map_count] = ft_strdup(line);
			if (!map_lines[map_count])
			{
				free(line);
				while (map_count > 0)
					free(map_lines[--map_count]);
				free(map_lines);
				free_g(g);
				close(fd);
				return (NULL);
			}
			map_count++;
		}
		// Ignorar líneas vacías
		
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	
	// Crear el mapa final
	if (map_count == 0)
	{
		printf("Error: No se encontraron líneas de mapa\n");
		free(map_lines);
		free_g(g);
		return (NULL);
	}
	
	if (!create_map(g, map_lines, map_count))
	{
		while (map_count > 0)
			free(map_lines[--map_count]);
		free(map_lines);
		free_g(g);
		return (NULL);
	}
	
	// Liberar el array temporal
	while (map_count > 0)
		free(map_lines[--map_count]);
	free(map_lines);
	
	return (g);
}
