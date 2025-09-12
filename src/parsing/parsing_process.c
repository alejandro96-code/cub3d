/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 00:00:00 by aleja             #+#    #+#             */
/*   Updated: 2025/09/12 17:16:24 by alejanr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Handles negative parsing results and triggers appropriate error messages */
int	handle_negative_result(int result, t_parse_data *data)
{
	if (result == -1)
		parsing_error(ERROR_CFG_AFTER_MAP, data);
	else if (result == -2)
		parsing_error(ERROR_RGB_VALUES, data);
	else if (result == -3)
		parsing_error(ERROR_INCOMPLETE_CONFIG, data);
	else if (result == -8)
		parsing_error(ERROR_TEXTURE_DUPLICATE, data);
	else if (result == -9)
		parsing_error(ERROR_TEXTURE_INVALID, data);
	else if (result == -10)
		parsing_error(ERROR_COLOR_DUPLICATE, data);
	return (0);
}

/* Handles zero parsing results and cleans up resources */
int	handle_zero_result(char *line, char **map_lines, int map_count, t_g *g)
{
	t_parse_data	data;

	data.fd = 0;
	data.line = line;
	data.map_lines = map_lines;
	data.map_count = map_count;
	data.g = g;
	cleanup_parsing(&data);
	return (0);
}

/* Processes individual file lines and determines their type */
int	process_file_line(char *line, t_g *g, char **map_lines, int *map_count)
{
	if (is_config_line(line))
		return (handle_config_line(line, g));
	else if (line[0] != '\0' && (line[0] == ' ' || line[0] == '1'
			|| line[0] == '0'))
		return (handle_map_line(line, g, map_lines, map_count));
	else if (g->map_started && line[0] == '\0')
	{
		if (!g->map_finished)
			g->map_finished = 1;
	}
	else if (g->map_started)
		return (-1);
	return (1);
}

/* Handles parsing errors by cleaning up and exiting with error message */
void	parsing_error(const char *msg, t_parse_data *data)
{
	cleanup_parsing(data);
	error_exit(msg);
}

/* Main function that reads and processes all lines from the file */
int	read_and_process_lines(int fd, t_g *g, char **map_lines, int *map_count)
{
	char			*line;
	int				len;
	int				result;
	t_parse_data	data;

	*map_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = 0;
		result = process_file_line(line, g, map_lines, map_count);
		if (result < 0)
		{
			data = (t_parse_data){fd, line, map_lines, *map_count, g};
			return (handle_negative_result(result, &data));
		}
		else if (result == 0)
			return (handle_zero_result(line, map_lines, *map_count, g));
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}
