/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/24 22:41:09 by aleja            ###   ########.fr       */
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
void	validate_map_config(t_g *g)
{
	if (has_empty_line(g))
	{
		free_g(g);
		error_exit(ERROR_LINEA_VACIA);
	}
	if (!has_only_valid_chars(g))
	{
		free_g(g);
		error_exit(ERROR_CHAR);
	}
	if (!is_map_closed(g))
	{
		free_g(g);
		error_exit(ERROR_MAPA_NO_CERRADO);
	}
	if (!has_player(g))
	{
		free_g(g);
		error_exit(ERROR_PLAYERS);
	}
}

// Comprueba todos los errores iniciales y retorna 0 si hay error, 1 si todo OK
void	checks_all_errors(int argc, char **argv, t_g **g, t_mlx **mlx)
{
	if (argc != 2)
		error_exit(ERROR_ARGUMENTOS);
	// Primero verificar si el archivo existe
	if (!validate_file_access(argv[1]))
		error_exit(ERROR_FILE_ACCESS);
	// Luego verificar la extensión
	if (!validate_extension(argv[1]))
		error_exit(ERROR_EXTENSION);
	*g = parse_cub_file(argv[1]);
	if (!*g)
	{
		error_exit(ERROR_PARSEO);
	}
	validate_map_config(*g);
	*mlx = init_window(*g);
	if (!*mlx)
	{
		free_g(*g);
		error_exit(ERROR_MLX);
	}
}
