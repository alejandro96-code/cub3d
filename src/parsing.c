/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/08 12:31:07 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Devuelve 1 si la línea es de mapa, 0 en caso contrario
static int	parse_cub_line(char *line)
{
	if (line[0] == '\0')
		return (1);
	if (line[0] == ' ' || line[0] == '1' || line[0] == '0')
		return (1);
	else
		return (0);
}

// Cuenta cuántas líneas de mapa hay en el archivo
static int	count_map_lines(const char *filename)
{
	int		fd;
	char	*line;
	int		count;
	int		len;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	while ((line = get_next_line(fd)))
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = 0;
		if (parse_cub_line(line))
			count++;
		free(line);
	}
	close(fd);
	return (count);
}

// Guarda las líneas de mapa en un array previamente reservado
static int	fill_map_lines(const char *filename, char **lines, int count)
{
	int		fd;
	char	*line;
	int		i;
	int		len;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)))
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = 0;
		if (parse_cub_line(line))
		{
			if (i < count)
				lines[i++] = ft_strdup(line);
		}
		else if (line[0] == '\0' && i < count)
			lines[i++] = ft_strdup("");
		free(line);
	}
	close(fd);
	return (i == count);
}

// Orquesta el proceso de contar y guardar líneas de mapa
static int	process_map_lines(const char *filename, char ***lines_out,
		int *count_out)
{
	int		count;
	char	**lines;
	int		i;

	count = count_map_lines(filename);
	if (count <= 0)
		return (0);
	lines = malloc(count * sizeof(char *));
	if (!lines)
		return (0);
	if (!fill_map_lines(filename, lines, count))
	{
		i = 0;
		while (i < count)
		{
			free(lines[i]);
			i++;
		}
		free(lines);
		return (0);
	}
	*lines_out = lines;
	*count_out = count;
	return (1);
}

// Crea el mapa en cfg a partir de las líneas procesadas
static int	create_map(t_cub_config *cfg, char **lines, int count)
{
	int	l;
	int	i;

	cfg->map = malloc(count * sizeof(char *));
	if (!cfg->map)
		return (0);
	cfg->map_height = count;
	cfg->map_width = 0;
	i = 0;
	while (i < count)
	{
		cfg->map[i] = ft_strdup(lines[i]);
		l = ft_strlen(lines[i]);
		if (l > cfg->map_width)
			cfg->map_width = l;
		i++;
	}
	return (1);
}

// Auxiliar de parse_cub_file_lines (superaba 25 lineas)
static void	free_lines_array(char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

/*
	Lee todas las líneas del archivo .cub,
	las procesa y construye el mapa y la configuración
*/
static int	parse_cub_file_lines(const char *filename, t_cub_config *cfg)
{
	char	**lines;
	int		count;

	lines = NULL;
	count = 0;
	if (!process_map_lines(filename, &lines, &count))
		return (0);
	if (!create_map(cfg, lines, count))
	{
		free_lines_array(lines, count);
		return (0);
	}
	free_lines_array(lines, count);
	return (1);
}

/*
	Función principal: abre el archivo .cub,
	reserva memoria y llama al parser de líneas
*/
t_cub_config	*parse_cub_file(const char *filename)
{
	int				fd;
	t_cub_config	*cfg;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	cfg = ft_calloc(1, sizeof(t_cub_config));
	if (!cfg)
	{
		close(fd);
		return (NULL);
	}
	// Inicializar colores por defecto
	cfg->floor_color = 0x00BFFF;   // Azul (DeepSkyBlue)
	cfg->ceiling_color = 0x7CFC00; // Verde claro (LawnGreen)
	if (!parse_cub_file_lines(filename, cfg))
	{
		free_cub_config(cfg);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (cfg);
}
