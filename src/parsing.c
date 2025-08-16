/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/16 13:23:24 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
static int	parse_cub_file_lines(const char *filename, t_g *g)
{
	char	**lines;
	int		count;

	lines = NULL;
	count = 0;
	if (!process_map_lines(filename, &lines, &count))
		return (0);
	if (!create_map(g, lines, count))
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
t_g	*parse_cub_file(const char *filename)
{
	int		fd;
	t_g	*g;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	g = ft_calloc(1, sizeof(t_g));
	if (!g)
	{
		close(fd);
		return (NULL);
	}
	g->floor_color = 0x00BFFF;
	g->ceiling_color = 0x7CFC00;
	if (!parse_cub_file_lines(filename, g))
	{
		free_g(g);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (g);
}
