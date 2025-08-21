/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:34:38 by aleja             #+#    #+#             */
/*   Updated: 2025/08/21 17:32:22 by alejanr2         ###   ########.fr       */
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

// Función auxiliar para eliminar espacios al inicio de una cadena
char	*trim_whitespace(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

// Función auxiliar para procesar y asignar una textura
static int	assign_texture(char *line, int prefix_len, char **texture_dest)
{
	char	*path;
	char	*trimmed_path;

	path = trim_whitespace(line + prefix_len);
	trimmed_path = ft_strtrim(path, " \t");
	if (!trimmed_path)
		return (0);
	*texture_dest = trimmed_path;
	return (1);
}

// Parsea una línea de textura (NO, SO, WE, EA)
int	parse_texture_line(char *line, t_g *g)
{
	line = trim_whitespace(line);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (assign_texture(line, 3, &g->north_texture));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (assign_texture(line, 3, &g->south_texture));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (assign_texture(line, 3, &g->west_texture));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (assign_texture(line, 3, &g->east_texture));
	return (0);
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

// Inicializa la estructura g y los buffers necesarios
static t_g	*init_parsing_structures(int fd, char ***map_lines)
{
	t_g	*g;

	g = ft_calloc(1, sizeof(t_g));
	if (!g)
	{
		close(fd);
		return (NULL);
	}
	*map_lines = malloc(100 * sizeof(char *));
	if (!*map_lines)
	{
		close(fd);
		free(g);
		return (NULL);
	}
	return (g);
}

// Procesa una línea del archivo .cub
static int	process_file_line(char *line, t_g *g, char **map_lines, int *map_count)
{
	if (is_config_line(line))
	{
		if (!parse_texture_line(line, g) && !parse_color_line(line, g))
			return (0);
	}
	else if (line[0] != '\0' && (line[0] == ' ' || line[0] == '1' || line[0] == '0'))
	{
		map_lines[*map_count] = ft_strdup(line);
		if (!map_lines[*map_count])
			return (0);
		(*map_count)++;
	}
	return (1);
}

// Lee y procesa todas las líneas del archivo
static int	read_and_process_lines(int fd, t_g *g, char **map_lines, int *map_count)
{
	char	*line;
	int		len;

	*map_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = 0;
		
		if (!process_file_line(line, g, map_lines, map_count))
		{
			cleanup_parsing(fd, line, map_lines, *map_count, g);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
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
	char	**map_lines;
	int		map_count;

	if (!validate_file_access(f))
		return (NULL);
	fd = open(f, O_RDONLY);
	if (fd < 0)
		return (NULL);
	g = init_parsing_structures(fd, &map_lines);
	if (!g)
		return (NULL);
	if (!read_and_process_lines(fd, g, map_lines, &map_count))
		return (NULL);
	close(fd);
	if (!validate_complete_parsing(g, map_lines, map_count))
		return (NULL);
	if (!create_map(g, map_lines, map_count))
	{
		cleanup_map_lines(map_lines, map_count);
		free_g(g);
		return (NULL);
	}
	cleanup_map_lines(map_lines, map_count);
	return (g);
}
