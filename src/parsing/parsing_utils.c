/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 00:00:00 by aleja             #+#    #+#             */
/*   Updated: 2025/08/26 00:06:51 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Pads map rows with spaces to make all rows the same width */
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

/* Removes leading whitespace characters from a string */
char	*trim_whitespace(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

/* Assigns texture path to the appropriate texture destination */
static int	assign_texture(char *line, int prefix_len, char **texture_dest)
{
	char	*path;
	char	*trimmed_path;

	path = trim_whitespace(line + prefix_len);
	trimmed_path = ft_strtrim(path, " \t");
	if (!trimmed_path)
		return (0);
	if (*texture_dest)
		free(*texture_dest);
	*texture_dest = trimmed_path;
	return (1);
}

/* Parses texture configuration lines (NO, SO, WE, EA) */
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

/* Creates and initializes the game map from parsed lines */
int	create_map(t_g *g, char **lines, int count)
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
