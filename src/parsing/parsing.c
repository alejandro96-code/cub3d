/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:34:38 by aleja             #+#    #+#             */
/*   Updated: 2025/08/26 00:06:51 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Initializes parsing structures and allocates memory for the game structure */
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

/* Main parser function that processes .cub file and returns game structure */
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
	if (!validate_and_create_map(g, map_lines, map_count))
		return (NULL);
	cleanup_map_lines(map_lines, map_count);
	return (g);
}
