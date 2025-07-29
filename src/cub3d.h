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

#ifndef CUB3D_H
# define CUB3D_H

//librerias usadas
# include "../mlx/mlx.h" //mlx
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
#include <string.h>

//chars usados para crear el mapa
# define PLAYER_N 'N'
# define PLAYER_S 'S'
# define PLAYER_W 'W'
# define PLAYER_E 'E'
# define FLOOR '0'
# define WALL '1'

# define ERROR_EXTENSION "Error: Extension de archivo invalida\n"
# define ERROR_ARGUMENTOS "Error: Nº de argumentos invalido\n"

//main
int		main(int argc, char **argv);



//parsing
int validate_extension(const char *filename);
int open_cub_file(const char *filename);
int read_cub_file(const char *filename);

#endif