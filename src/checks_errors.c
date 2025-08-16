/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/16 13:45:38 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Valida la extensión del archivo .cub
int	validate_extension(const char *f)
{
	int	len;

	len = 0;
	while (f[len])
		len++;
	if (len < 4)
		return (0);
	return (f[len - 4] == '.' && f[len - 3] == 'c' && f[len - 2] == 'u' && f[len - 1] == 'b');
}

// validaciones del mapa
static int	validate_map_config(t_g *g)
{
	if (has_empty_line(g))
		return (printf(ERROR_LINEA_VACIA), 0);
	if (!has_only_valid_chars(g))
		return (printf(ERROR_CHAR), 0);
	if (!is_map_closed(g))
		return (printf(ERROR_MAPA_NO_CERRADO), 0);
	if (!has_player(g))
		return (printf(ERROR_PLAYERS), 0);
	return (1);
}

// Comprueba todos los errores iniciales y retorna 0 si hay error, 1 si todo OK
int	checks_all_errors(int argc, char **argv, t_g **g, t_mlx **mlx)
{
	if (argc != 2)
		return (printf(ERROR_ARGUMENTOS), 0);
	if (!validate_extension(argv[1]))
		return (printf(ERROR_EXTENSION), 0);
	*g = parse_cub_file(argv[1]);
	if (!*g)
		return (printf(ERROR_PARSEO), 0);
	if (!validate_map_config(*g))
	{
		free_g(*g);
		return (0);
	}
	*mlx = init_window(*g);
	if (!*mlx)
	{
		free_g(*g);
		return (printf(ERROR_MLX), 0);
	}
	return (1);
}
