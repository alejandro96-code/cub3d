
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

// Comprueba que exista exactamente un jugador en el mapa (N, S, E, W)
int has_player(char **map, int width, int height)
{
	int x = 0;
	int y = 0;
	int count = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
				count++;
			x++;
		}
		y++;
	}
	return (count == 1);
}

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
	int	x;
	int	y;

	x = 0;
	y = 0;
	// Revisar primera y última fila
	while (x < width)
	{
		if (map[0][x] != '1' && map[0][x] != '\0')
			return (0);
		if (map[height-1][x] != '1' && map[height-1][x] != '\0')
			return (0);
		x++;
	}
	// Revisar primera y última columna de cada fila
	while (y < height)
	{
		if (map[y][0] != '1')
			return (0);
		if (map[y][width-1] != '1' && map[y][width-1] != '\0')
			return (0);
		y++;
	}
	return (1);
}

// Comprueba todos los errores iniciales y retorna 0 si hay error, 1 si todo OK
int checksAllErrors(int argc, char **argv, t_cub_config **cfg, t_mlx **mlx)
{
	if (argc != 2)
		return (printf(ERROR_ARGUMENTOS), 0);
	if (!validate_extension(argv[1]))
		return (printf(ERROR_EXTENSION), 0);
	*cfg = parse_cub_file(argv[1]);
	if (!*cfg)
		return (printf(ERROR_PARSEO), 0);
	if (!is_map_closed((*cfg)->map, (*cfg)->map_width, (*cfg)->map_height))
	{
		free_cub_config(*cfg);
		return (printf(ERROR_MAPA_NO_CERRADO), 0);
	}
	if (!has_player((*cfg)->map, (*cfg)->map_width, (*cfg)->map_height))
	{
		free_cub_config(*cfg);
		return (printf(ERROR_PLAYERS), 0);
	}
	*mlx = init_window(*cfg);
	if (!*mlx)
	{
		free_cub_config(*cfg);
		return (printf(ERROR_MLX), 0);
	}
	return 1;
}
