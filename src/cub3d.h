/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/07 02:43:22 by ybahri           ###   ########.fr       */
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
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

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
# define ERROR_CHAR "Error: Caracter incorrecto en la creacion del mapa\n"
# define ERROR_LINEA_VACIA "Error: Se ha encontrado una linea vacia\n"

// BONUS
# define MINIMAP_CELL_SIZE 8
# define MINIMAP_MARGIN 16
# define MINIMAP_WALL_COLOR 0x888888
# define MINIMAP_FLOOR_COLOR 0x222222

// EVENTOS Y TECLAS
# define KeyPress		2
# define KeyPressMask	(1L<<0)

// DEFINICIONES DE TECLAS
# define KEY_ESC		65307
# define KEY_W			119
# define KEY_S			115
# define KEY_A			97
# define KEY_D			100
# define KEY_LEFT		65361
# define KEY_RIGHT		65363

// VELOCIDADES DE MOVIMIENTO Y ROTACIÓN
# define MOVE_SPEED		0.1
# define ROT_SPEED		0.05

typedef struct s_texture
{
	void		*img_ptr;
	int			*buffer;
	int			width;
	int			height;
}				t_texture;

// Estructura principal de configuración
typedef struct s_cub_config
{
	// COLORES DEL ENTORNO
	int			floor_color;	// Color del suelo (formato RGB hex)
	int			ceiling_color;	// Color del techo (formato RGB hex)
	// DATOS DEL MAPA
	char		**map;			// Array 2D con el mapa del juego
	int			map_height;		// Número de filas del mapa
	int			map_width;		// Número de columnas del mapa
	t_texture	textures[4];	// Array de texturas (N, S, E, O)
}				t_cub_config;

// Estructura para la ventana y contexto MLX
typedef struct s_mlx
{
	// PUNTEROS MLX
	void		*mlx_ptr;		// Puntero a la instancia MLX principal
	void		*win_ptr;		// Puntero a la ventana creada
	// DIMENSIONES DE VENTANA
	int			width;
	int			height;
	// FRAMEBUFFER
	void		*img_ptr;
	int			*pixels;
	int			bpp;
	int			line_len;
	int			endian;
}				t_mlx;

// Estructura para el jugador (posición, dirección y plano de cámara)
typedef struct s_player
{
	// POSICIÓN EN EL MUNDO
	double		x;				// Coordenada X del jugador en el mapa
	double		y;				// Coordenada Y del jugador en el mapa
	// VECTOR DE DIRECCIÓN
	double		dir_x;			// Componente X del vector dirección
	double		dir_y;			// Componente Y del vector dirección
	// PLANO DE CÁMARA (para FOV)
	double		plane_x;		// Componente X del plano de cámara
	double		plane_y;		// Componente Y del plano de cámara
}				t_player;

typedef struct s_raycast
{
	// CONFIGURACIÓN DEL RAYO
	double		camera_x;		// Posición x en el plano de cámara (-1 a 1)
	double		ray_dir_x;		// Dirección X del rayo en el mundo
	double		ray_dir_y;		// Dirección Y del rayo en el mundo
	// POSICIÓN EN EL MAPA
	int			map_x;			// Coordenada X en el grid del mapa
	int			map_y;			// Coordenada Y en el grid del mapa
	// CÁLCULOS DE DISTANCIA DDA
	double		delta_dist_x;	// Distancia para cruzar una celda en X
	double		delta_dist_y;	// Distancia para cruzar una celda en Y
	double		side_dist_x;	// Distancia hasta el próximo lado X del grid
	double		side_dist_y;	// Distancia hasta el próximo lado Y del grid
	// PASOS Y DIRECCIÓN
	int			step_x;			// Dirección del paso en X: +1 o -1
	int			step_y;			// Dirección del paso en Y: +1 o -1
	// RESULTADOS DE COLISIÓN
	int			side;			// Qué lado de pared se golpeó (0=X, 1=Y)
	double		perp_wall_dist;	// Distancia perpendicular a la pared
	// CÁLCULOS DE RENDERIZADO
	int			line_height;	// Altura de la línea a dibujar en pantalla
	int			draw_start;		// Píxel Y donde empezar a dibujar la pared
	int			draw_end;		// Píxel Y donde terminar de dibujar la pared
	// INFORMACIÓN DE DIBUJADO
	int			x;				// Columna actual de píxeles renderizando
	int			color;			// Color calculado para esta columna
	int			tex_x;			// Coordenada X en la textura
}				t_raycast;

// Estructura para pasar datos a los hooks
typedef struct s_hook_data
{
	t_mlx			*mlx;
	t_cub_config	*cfg;
	t_player		*player;
}				t_hook_data;

// main.c
int				main(int argc, char **argv);

// checks_errors.c
int				validate_extension(const char *filename);
int				checksAllErrors(int argc, char **argv, t_cub_config **cfg,
					t_mlx **mlx);
int				has_player(t_cub_config *cfg);
int				has_only_valid_chars(t_cub_config *cfg);
int				has_empty_line(t_cub_config *cfg);
int				is_map_closed(t_cub_config *cfg);

// parsing.c
t_cub_config	*parse_cub_file(const char *filename);

// free.c
void			free_cub_config(t_cub_config *cfg);

// init_window.c
t_mlx			*init_window(const t_cub_config *cfg);
void			destroy_window(t_mlx *mlx);
int				close_window(t_mlx *mlx);

// init_player.c
void			init_player_from_map(t_player *player, t_cub_config *cfg);

// renderScene.c
void			render_scene(t_mlx *mlx, t_cub_config *cfg, t_player *player);

// raycast_calc.c
void			calculate_ray_direction(const t_player *player, t_mlx *mlx,
					t_raycast *v);
void			calculate_step_and_side_dist(const t_player *player,
					t_raycast *v);
int				raycast_dda(const t_cub_config *cfg, t_raycast *v);
void			calculate_perp_wall_and_lineheight(t_mlx *mlx, t_player *player,
					t_raycast *v);
void			calculate_draw_limits(t_mlx *mlx, t_raycast *v);

// drawColors.c
void			draw_column_colors(t_mlx *mlx, t_cub_config *cfg, t_raycast *v);

// bonus_minimap.c
void			bonus_minimap(t_mlx *mlx, t_cub_config *cfg);

// hooks.c
void			setup_hooks(t_mlx *mlx, t_cub_config *cfg, t_player *player);
int				key_press(int keycode, t_hook_data *data);
int				close_window_hook(t_hook_data *data);

// player_control.c
void			move_player(int keycode, t_cub_config *cfg, t_player *player);
void			rotate_view(int keycode, t_player *player);

// utils.c
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

// textures.c
void			load_textures(t_mlx *mlx, t_cub_config *cfg);

// draw.c
void			draw_floor_ceiling(t_mlx *mlx, t_cub_config *cfg, t_raycast *v);
void			draw_wall_textures(t_mlx *mlx, t_cub_config *cfg, t_player *player, t_raycast *v);

#endif
