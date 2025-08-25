/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:34:38 by aleja             #+#    #+#             */
/*   Updated: 2025/08/26 01:10:36 by ybahri           ###   ########.fr       */
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

/* Unified function to free string arrays */
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

/* Free map lines array with known count (used by parser) */
void	cleanup_map_lines(char **array, int count)
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

/* Clean up file and current line */
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
		temp_line = get_next_line(fd);
		while (temp_line != NULL)
		{
			free(temp_line);
			temp_line = get_next_line(fd);
		}
		close(fd);
	}
}

/* Complete cleanup during parsing */
void	cleanup_parsing(t_parse_data *data)
{
	char	*temp_line;

	if (data->line)
		free(data->line);
	temp_line = get_next_line(data->fd);
	while (temp_line != NULL)
	{
		free(temp_line);
		temp_line = get_next_line(data->fd);
	}
	cleanup_map_lines(data->map_lines, data->map_count);
	free_g(data->g);
	close(data->fd);
}
