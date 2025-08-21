/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:45:00 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/21 12:38:27 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Devuelve 1 si la línea es de mapa (espacios valido), 0 en caso contrario
static int	parse_cub_line(char *line)
{
	int		i;
	char	c;

	if (!line || line[0] == '\0')
		return (0);
	i = 0;
	while (line[i] != '\0')
	{
		c = line[i];
		if (c != ' ' && c != '\t' && c != '0' && c != '1'
			&& c != 'N' && c != 'S' && c != 'E' && c != 'W')
			return (0);
		i++;
	}
	return (1);
}

// Cuenta cuántas líneas de mapa hay en el archivo
static int	count_map_lines(const char *f)
{
	int		fd;
	char	*line;
	int		count;
	int		len;

	count = 0;
	fd = open(f, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = 0;
		if (parse_cub_line(line))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

// Guarda las líneas de mapa en un array previamente reservado
static int	fill_map_lines(const char *f, char **lines, int count)
{
	int		fd;
	char	*line;
	int		i;
	int		len;

	i = 0;
	fd = open(f, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line && i < count)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = 0;
		if (parse_cub_line(line))
		{
			lines[i] = ft_strdup(line);
			if (!lines[i])
			{
				free(line);
				close(fd);
				return (0);
			}
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i == count);
}

// Orquesta el proceso de contar y guardar líneas de mapa
int	process_map_lines(const char *f, char ***lines_out,
		int *count_out)
{
	int		count;
	char	**lines;
	int		i;

	count = count_map_lines(f);
	if (count <= 0)
		return (0);
	lines = malloc(count * sizeof(char *));
	if (!lines)
		return (0);
	if (!fill_map_lines(f, lines, count))
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
