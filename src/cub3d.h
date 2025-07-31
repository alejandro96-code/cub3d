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

// librerias usadas
# include "../mlx/mlx.h"
# include "../src/gnl/get_next_line.h"
# include "../src/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stddef.h>

# define PLAYER_N 'N'
# define PLAYER_S 'S'
# define PLAYER_W 'W'
# define PLAYER_E 'E'
# define FLOOR '0'
# define WALL '1'
# define TILE_SIZE 64

# define ERROR_EXTENSION "Error: Extension de archivo invalida\n"
# define ERROR_ARGUMENTOS "Error: Nº de argumentos invalido\n"
# define ERROR_PARSEO "Error: No existe el mapa .cub\n"
# define ERROR_MLX "Error: No se pudo inicializar la ventana MLX\n"
# define ERROR_MAPA_NO_CERRADO "Error: El mapa no está completamente cerrado\n"
# define ERROR_PLAYERS "Error: Debe haber exactamente un jugador en el mapa\n"

// Estructura principal de configuración
typedef struct s_cub_config
{

	int			floor_color;
	int			ceiling_color;
	char 		**map;
	int			map_height;
	int			map_width;
}				t_cub_config;

// Estructura para la ventana y contexto MLX
typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			width;
	int			height;
}				t_mlx;

// Estructura para el jugador (posición, dirección y plano de cámara)
typedef struct s_player
{
	double x, y;
	double dir_x, dir_y;
	double plane_x, plane_y;
}				t_player;

// Estructura para la información del rayo
typedef struct s_rayinfo
{
	double		ray_dir_x;
	double		ray_dir_y;
}				t_rayinfo;

// Estructura para agrupar los parámetros de pintado
typedef struct s_paintinfo
{
	t_mlx		*mlx;
	int			x;
	int			draw_start;
	int			draw_end;
	int			color;
	int			side;
}				t_paintinfo;

typedef struct s_raycast_vars {
	t_rayinfo rayinfo;
	t_paintinfo paintinfo;
	double  camera_x;
	double  ray_dir_x;
	double  ray_dir_y;
	int     map_x;
	int     map_y;
	double  delta_dist_x;
	double  delta_dist_y;
	int     side;
	double  perp_wall_dist;
	int     line_height;
	int     draw_start;
	int     draw_end;
	int     step_x;
	int     step_y;
	double  side_dist_x;
	double  side_dist_y;
	int     x;

}   t_raycast_vars;

//funciones
int				main(int argc, char **argv);


void			init_player_from_map(t_player *player, t_cub_config *cfg);


int				validate_extension(const char *filename);
t_cub_config	*parse_cub_file(const char *filename);
void			free_cub_config(t_cub_config *cfg);


t_mlx			*init_window(const t_cub_config *cfg);
void			destroy_window(t_mlx *mlx);
int				close_window(t_mlx *mlx);

void			render_scene(t_mlx *mlx, t_cub_config *cfg, t_player *player);


void calculate_ray_direction(const t_player *player, t_mlx *mlx, t_raycast_vars *v, int x);

void calculate_step_and_side_dist(const t_player *player, t_raycast_vars *v);

int raycast_dda(const t_cub_config *cfg, t_raycast_vars *v);

void calculate_perp_wall_and_lineheight(t_mlx *mlx, t_player *player, t_raycast_vars *v);

void calculate_draw_limits(t_mlx *mlx, t_raycast_vars *v);


void draw_column_colors(t_paintinfo *p, t_rayinfo *ray);

int is_map_closed(char **map, int width, int height);
int checksAllErrors(int argc, char **argv, t_cub_config **cfg, t_mlx **mlx);
int has_player(char **map, int width, int height);


#endif