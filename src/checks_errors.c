/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/07/29 16:38:20 by alejanr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_extension(const char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len < 4)
		return (0);
	return (filename[len - 4] == '.' && filename[len - 3] == 'c' \
&& filename[len - 2] == 'u' && filename[len - 1] == 'b');
}

// Verifica que el mapa esté completamente cerrado por '1'
int is_map_closed(char **map, int width, int height)
{
	int x, y;
	// Revisar primera y última fila
	for (x = 0; x < width; x++)
	{
		if (map[0][x] != '1' && map[0][x] != '\0')
			return (0);
		if (map[height-1][x] != '1' && map[height-1][x] != '\0')
			return (0);
	}
	// Revisar primera y última columna de cada fila
	for (y = 0; y < height; y++)
	{
		if (map[y][0] != '1')
			return (0);
		if (map[y][width-1] != '1' && map[y][width-1] != '\0')
			return (0);
	}
	return (1);
}
