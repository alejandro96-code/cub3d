/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:34:38 by aleja             #+#    #+#             */
/*   Updated: 2025/08/24 23:04:03 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_g(t_g *g)
{
	int	i;

	if (!g)
		return ;
	if (g->map)
	{
		i = 0;
		while (i < g->map_height)
		{
			free(g->map[i]);
			i++;
		}
		free(g->map);
	}
	if (g->north_texture)
		free(g->north_texture);
	if (g->south_texture)
		free(g->south_texture);
	if (g->east_texture)
		free(g->east_texture);
	if (g->west_texture)
		free(g->west_texture);
	free(g);
}

// Función unificada para liberar arrays de strings
void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// Función unificada para liberar arrays de strings con count conocido
void	free_string_array_count(char **array, int count)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (i < count)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}

// Función para cerrar archivo y liberar línea actual
void	cleanup_file_and_line(int fd, char **line)
{
	char	*temp_line;

	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	if (fd >= 0)
	{
		while ((temp_line = get_next_line(fd)) != NULL)
			free(temp_line);
		close(fd);
	}
}

// Libera el array de líneas del mapa
void	cleanup_map_lines(char **map_lines, int count)
{
	while (count > 0)
		free(map_lines[--count]);
	free(map_lines);
}

// Función de limpieza completa durante el parsing
void	cleanup_parsing(t_parse_data *data)
{
	char	*temp_line;

	if (data->line)
		free(data->line);
	while ((temp_line = get_next_line(data->fd)) != NULL)
		free(temp_line);
	cleanup_map_lines(data->map_lines, data->map_count);
	free_g(data->g);
	close(data->fd);
}
