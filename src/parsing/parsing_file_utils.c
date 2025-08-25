/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 00:00:00 by aleja             #+#    #+#             */
/*   Updated: 2025/08/26 00:06:46 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_file_access(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	validate_map_lines_count(int map_count)
{
	if (map_count == 0)
		return (-7);
	return (1);
}

int	validate_complete_parsing(t_g *g, char **map_lines, int map_count)
{
	int	result;

	(void)map_lines;
	result = validate_config_completeness(g);
	if (result < 0)
		return (result);
	result = validate_map_lines_count(map_count);
	if (result < 0)
		return (result);
	return (1);
}
