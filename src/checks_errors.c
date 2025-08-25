/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/26 00:41:41 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Validates .cub file extension */
int	validate_extension(const char *f)
{
	int	len;

	len = 0;
	while (f[len])
		len++;
	if (len < 4)
		return (0);
	return (f[len - 4] == '.' && f[len - 3] == 'c'
		&& f[len - 2] == 'u' && f[len - 1] == 'b');
}

/* Map validations */
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

/* Checks all initial errors */
void	checks_all_errors(int argc, char **argv, t_g **g, t_mlx **mlx)
{
	if (argc != 2)
		error_exit(ERROR_ARGUMENTOS);
	if (!validate_file_access(argv[1]))
		error_exit(ERROR_FILE_ACCESS);
	if (!validate_extension(argv[1]))
		error_exit(ERROR_EXTENSION);
	*g = parse_cub_file(argv[1]);
	if (!*g)
		error_exit(ERROR_PARSEO);
	validate_map_config(*g);
	*mlx = init_window(*g);
	if (!*mlx)
	{
		free_g(*g);
		error_exit(ERROR_MLX);
	}
}
