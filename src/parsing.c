/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:34:38 by aleja             #+#    #+#             */
/*   Updated: 2025/08/21 16:14:37 by alejanr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Rellena con espacios hasta map_width para evitar '\0' en filas cortas */
static void	pad_map_to_rect(t_g *g)
{
	int		y;
	int		len;
	char	*row;

	y = 0;
	while (y < g->map_height)
	{
		len = (int)ft_strlen(g->map[y]);
		if (len < g->map_width)
		{
			row = (char *)malloc(g->map_width + 1);
			if (!row)
				return ;
			ft_memset(row, ' ', g->map_width);
			ft_memcpy(row, g->map[y], len);
			row[g->map_width] = '\0';
			free(g->map[y]);
			g->map[y] = row;
		}
		y++;
	}
}

static void	rtrim(char *s)
{
	int	len;

	if (!s)
		return ;
	len = (int)ft_strlen(s);
	while (len > 0 && (s[len - 1] == ' ' || s[len - 1] == '\t'))
	{
		s[len - 1] = '\0';
		len--;
	}
}

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
		rtrim(path);
		g->north_texture = ft_strdup(path);
		return (g->north_texture != NULL);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		path = trim_whitespace(line + 3);
		rtrim(path);
		g->south_texture = ft_strdup(path);
		return (g->south_texture != NULL);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		path = trim_whitespace(line + 3);
		rtrim(path);
		g->west_texture = ft_strdup(path);
		return (g->west_texture != NULL);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		path = trim_whitespace(line + 3);
		rtrim(path);
		g->east_texture = ft_strdup(path);
		return (g->east_texture != NULL);
	}
	return (0);
}

// Parsea valores RGB desde una cadena "r,g,b"
static int	parse_rgb_values(char *rgb_str, int *color)
{
	char	**values;
	int		r;
	int		g;
	int		b;
	int		i;

	rgb_str = trim_whitespace(rgb_str);
	rtrim(rgb_str);
	values = ft_split(rgb_str, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		printf(ERROR_RGB_FORMAT);
		if (values)
		{
			i = 0;
			while (values[i])
			{
				free(values[i]);
				i++;
			}
			free(values);
		}
		return (0);
	}
	r = ft_atoi(trim_whitespace(values[0]));
	g = ft_atoi(trim_whitespace(values[1]));
	b = ft_atoi(trim_whitespace(values[2]));
	i = 0;
	while (values[i])
	{
		free(values[i]);
		i++;
	}
	free(values);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        {
		printf(ERROR_RGB_VALUES);
		return (0);
	}
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
		if (parse_rgb_values(rgb_str, &g->ceiling_color))
		{
			g->ceiling_color_set = 1;
			return (1);
		}
		return (0);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		rgb_str = trim_whitespace(line + 2);
		if (parse_rgb_values(rgb_str, &g->floor_color))
		{
			g->floor_color_set = 1;
			return (1);
		}
		return (0);
	}
	return (0);
}

// Verifica si una línea es de configuración (textura o color)
static int	is_config_line(char *line)
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
static int	validate_config_completeness(t_g *g)
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
	pad_map_to_rect(g);
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
	map_lines = malloc(100 * sizeof(char *));
	if (!map_lines)
	{
		close(fd);
		free(g);
		return (NULL);
	}
	map_count = 0;
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
				free(line);
				// Leer todas las líneas restantes para cerrar get_next_line correctamente
				while ((line = get_next_line(fd)) != NULL)
					free(line);
				while (map_count > 0)
					free(map_lines[--map_count]);
				free(map_lines);
				free_g(g);
				close(fd);
				return (NULL);
			}
		}
		else if (line[0] != '\0' && (line[0] == ' ' || line[0] == '1'
				|| line[0] == '0'))
		{
			map_lines[map_count] = ft_strdup(line);
			if (!map_lines[map_count])
			{
				free(line);
				// Leer todas las líneas restantes para cerrar get_next_line correctamente
				while ((line = get_next_line(fd)) != NULL)
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
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!validate_config_completeness(g))
	{
		while (map_count > 0)
			free(map_lines[--map_count]);
		free(map_lines);
		free_g(g);
		return (NULL);
	}
	if (map_count == 0)
	{
		printf(ERROR_NO_MAP_LINES);
		while (map_count > 0)
			free(map_lines[--map_count]);
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
	while (map_count > 0)
		free(map_lines[--map_count]);
	free(map_lines);
	return (g);
}
