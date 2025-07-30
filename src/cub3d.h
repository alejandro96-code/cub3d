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

// Estructura principal de configuración
typedef struct s_cub_config {
    char *texture_north;
    char *texture_south;
    char *texture_east;
    char *texture_west;
    int  floor_color;
    int  ceiling_color;
    char **map; // Matriz de chars (mapa)
    int  map_height;
    int  map_width;
}   t_cub_config;

// Estructura para la ventana y contexto MLX
typedef struct s_mlx {
    void *mlx_ptr;
    void *win_ptr;
    int width;
    int height;
} t_mlx;

//librerias usadas
# include "../mlx/mlx.h" //mlx
# include "../src/gnl/get_next_line.h" //get_next_line
# include "../src/libft/libft.h" //libft
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# include <unistd.h>
# include <string.h>

//chars usados para crear el mapa
# define PLAYER_N 'N'
# define PLAYER_S 'S'
# define PLAYER_W 'W'
# define PLAYER_E 'E'
# define FLOOR '0'
# define WALL '1'
# define TILE_SIZE 64

# define ERROR_EXTENSION "Error: Extension de archivo invalida\n"
# define ERROR_ARGUMENTOS "Error: Nº de argumentos invalido\n"
# define ERROR_PARSEO "Error: No se pudo parsear el archivo .cub\n"
# define ERROR_MLX "Error: No se pudo inicializar la ventana MLX\n"

//main
int		main(int argc, char **argv);

//parsing
int validate_extension(const char *filename);
t_cub_config *parse_cub_file(const char *filename);
void free_cub_config(t_cub_config *cfg);

//mlx
t_mlx *init_window(const t_cub_config *cfg);
void destroy_window(t_mlx *mlx);

#endif