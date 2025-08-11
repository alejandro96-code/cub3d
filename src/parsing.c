/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/08 13:24:07 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	cfg->floor_color = 0x00BFFF;
	cfg->ceiling_color = 0x7CFC00;
	if (!parse_cub_file_lines(filename, cfg))
	{
		free_cub_config(cfg);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (cfg);
}
