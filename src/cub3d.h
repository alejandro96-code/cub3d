/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/09/10 16:41:19 by aleja            ###   ########.fr       */
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

# define ERROR_EXTENSION "Extension de archivo invalida\n"
# define ERROR_ARGUMENTOS "Nº de argumentos invalido\n"
# define ERROR_PARSEO "No existe el mapa .cub\n"
# define ERROR_MLX "No se pudo inicializar la ventana MLX\n"
# define ERROR_MAPA_NO_CERRADO "El mapa no está completamente cerrado\n"
# define ERROR_PLAYERS "Debe haber exactamente un jugador en el mapa\n"
# define ERROR_CHAR "Caracter incorrecto en la creacion del mapa\n"
# define ERROR_LINEA_VACIA "Se ha encontrado una linea vacia\n"
# define ERROR_RGB_FORMAT "Formato RGB inválido.\n"
# define ERROR_RGB_VALUES "Valores RGB deben estar entre 0 y 255.\n"
# define ERROR_NO_TEXTURE "Falta textura del norte (NO)\n"
# define ERROR_SO_TEXTURE "Falta textura del sur (SO)\n"
# define ERROR_EA_TEXTURE "Falta textura del este (EA)\n"
# define ERROR_WE_TEXTURE "Falta textura del oeste (WE)\n"
# define ERROR_CEILING_COLOR "Falta color del cielo (C)\n"
# define ERROR_FLOOR_COLOR "Falta color del suelo (F)\n"
# define ERROR_NO_MAP_LINES "No se encontraron líneas de mapa\n"
# define ERROR_TEXTURE_LOAD "No se pudo cargar la textura\n"
# define ERROR_TEXTURE_BUFFER "No se pudo obtener el buffer de la textura\n"
# define ERROR_MISSING_TEXTURES "Faltan texturas en el archivo .cub\n"
# define ERROR_FILE_ACCESS "No se puede acceder al archivo\n"
# define ERROR_MEMORY "Error de memoria\n"
# define ERROR_MAP_ORDER "El mapa debe estar al final del archivo\n"
# define ERROR_CFG_AFTER_MAP "No se permiten configuraciones después del mapa\n"
# define ERROR_INCOMPLETE_CONFIG "Configuración incompleta antes del mapa\n"

// BONUS
# define MINIMAP_CELL_SIZE 8
# define MINIMAP_MARGIN 16
# define MINIMAP_WALL_COLOR 0x888888
# define MINIMAP_FLOOR_COLOR 0x222222

// EVENTOS Y TECLAS
# define KEYPRESS 2
# define KEYPRESSMASK 1

// DEFINICIONES DE TECLAS
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// VELOCIDADES DE MOVIMIENTO Y ROTACIÓN
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

// DEFINICIONES PARA LAS ESTRUCTURAS
# define IDX_NO 0
# define IDX_SO 1
# define IDX_EA 2
# define IDX_WE 3

// Estructura para la ventana y contexto MLX (se mantiene separada)
typedef struct s_mlx
{
	void	*mlx_ptr; // Puntero a la instancia MLX principal
	void	*win_ptr; // Puntero a la ventana creada
	int		width; //Dimension anchura
	int		height; //Dimension altura
	void	*img_ptr;
	int		*pixels;
	int		bpp;
	int		line_len;
	int		endian;
}			t_mlx;

// Estructura principal del juego que contiene todo
typedef struct s_g
{
	int		floor_color; // Color del suelo (formato RGB hex)
	int		ceiling_color; // Color del techo (formato RGB hex)
	int		floor_color_set; // Bandera: 1 si se configuró el color del suelo
	int		ceiling_color_set; // Bandera: 1 si se configuró el color del techo
	char	*north_texture; // Ruta textura norte (NO)
	char	*south_texture; // Ruta textura sur (SO)
	char	*east_texture; // Ruta textura este (EA)
	char	*west_texture; // Ruta textura oeste (WE)
	char	**map; // Array 2D con el mapa del juego
	int		map_height; // Número de filas del mapa
	int		map_width; // Número de columnas del mapa
	void	*tex_img_ptr[4]; // Punteros a imágenes de texturas
	int		*tex_buffer[4]; // Buffers de texturas
	int		tex_width[4]; // Anchos de texturas
	int		tex_height[4]; // Alturas de texturas
	double	player_x; // Coordenada X del jugador en el mapa
	double	player_y; // Coordenada Y del jugador en el mapa
	double	dir_x; // Componente X del vector dirección
	double	dir_y; // Componente Y del vector dirección
	double	plane_x; // Componente X del plano de cámara
	double	plane_y; // Componente Y del plano de cámara
	double	camera_x; // Posición x en el plano de cámara (-1 a 1)
	double	ray_dir_x; // Dirección X del rayo en el mundo
	double	ray_dir_y; // Dirección Y del rayo en el mundo
	int		map_x; // Coordenada X en el grid del mapa
	int		map_y; // Coordenada Y en el grid del mapa
	double	delta_dist_x; // Distancia para cruzar una celda en X
	double	delta_dist_y; // Distancia para cruzar una celda en Y
	double	side_dist_x; // Distancia hasta el próximo lado X del grid
	double	side_dist_y; // Distancia hasta el próximo lado Y del grid
	int		step_x; // Dirección del paso en X: +1 o -1
	int		step_y; // Dirección del paso en Y: +1 o -1
	int		side; // Qué lado de pared se golpeó (0=X, 1=Y)
	double	perp_wall_dist; // Distancia perpendicular a la pared
	int		line_height; // Altura de la línea a dibujar en pantalla
	int		draw_start; // Píxel Y donde empezar a dibujar la pared
	int		draw_end; // Píxel Y donde terminar de dibujar la pared
	int		x; // Columna actual de píxeles renderizando
	int		color; // Color calculado para esta columna
	int		tex_x; // Coordenada X en la textura
	int		current_pixel_y; // Y temporal para pixel actual
	int		current_pixel_color; // Color temporal para pixel actual
	int		map_started; // Flag para validar orden del archivo
	int		map_finished; // Flag para detectar cuando el mapa terminó
	t_mlx	*mlx; // Puntero a MLX para hooks
}			t_g;

// Estructura para datos de parsing (reduce número de parámetros)
typedef struct s_parse_data
{
	int		fd;
	char	*line;
	char	**map_lines;
	int		map_count;
	t_g		*g;
}			t_parse_data;

// main.c
int			main(int argc, char **argv);
// checks_errors.c
int			validate_extension(const char *f);
void		checks_all_errors(int argc, char **argv, t_g **g, t_mlx **mlx);
void		validate_map_config(t_g *g);
int			has_player(t_g *g);
int			has_only_valid_chars(t_g *g);
int			has_empty_line(t_g *g);
int			is_map_closed(t_g *g);
// parsing/parsing.c
t_g			*parse_cub_file(const char *f);
// parsing/parsing_utils.c
char		*trim_whitespace(char *str);
int			parse_texture_line(char *line, t_g *g);
int			create_map(t_g *g, char **lines, int count);
// parsing/parsing_colors.c
int			parse_color_line(char *line, t_g *g);
// parsing/parsing_validation.c
int			validate_map_start(t_g *g);
int			handle_config_line(char *line, t_g *g);
int			handle_map_line(char *line, t_g *g, char **map_lines,
				int *map_count);
int			validate_and_create_map(t_g *g, char **map_lines, int map_count);
// parsing/parsing_process.c
int			handle_negative_result(int result, t_parse_data *data);
int			handle_zero_result(char *line, char **map_lines, int map_count,
				t_g *g);
int			process_file_line(char *line, t_g *g, char **map_lines,
				int *map_count);
void		parsing_error(const char *msg, t_parse_data *data);
int			read_and_process_lines(int fd, t_g *g, char **map_lines,
				int *map_count);
// parsing/validate_parse_errors.c
int			parse_rgb_values(char *rgb_str, int *color);
int			is_config_line(char *line);
int			validate_config_completeness(t_g *g);
// parsing/parsing_file_utils.c
int			validate_file_access(const char *filename);
int			validate_map_lines_count(int map_count);
int			validate_complete_parsing(t_g *g, char **map_lines, int map_count);
// free.c
void		free_g(t_g *g);
// init_window.c
t_mlx		*init_window(const t_g *g);
void		destroy_window(t_mlx *mlx);
int			close_window(t_mlx *mlx);
// init_player.c
void		init_player_from_map(t_g *g);
// renderScene.c
void		render_scene(t_mlx *mlx, t_g *g);
// raycast_calc.c
void		calculate_ray_direction(t_g *g, t_mlx *mlx);
void		calculate_step_and_side_dist(t_g *g);
int			raycast_dda(t_g *g);
void		calculate_perp_wall_and_lineheight(t_mlx *mlx, t_g *g);
void		calculate_draw_limits(t_mlx *mlx, t_g *g);
// hooks.c
void		setup_hooks(t_g *g);
int			key_press(int keycode, t_g *g);
int			close_window_hook(t_g *g);
// player_control.c
void		move_player(int keycode, t_g *g);
void		rotate_view(int keycode, t_g *g);
// utils.c
void		my_mlx_pixel_put(t_g *g);
void		error_exit(const char *msg);
// free.c
void		free_string_array(char **array);
void		free_string_array_count(char **array, int count);
void		cleanup_file_and_line(int fd, char **line);
void		cleanup_map_lines(char **map_lines, int count);
void		cleanup_parsing(t_parse_data *data);
// textures.c
void		load_textures(t_mlx *mlx, t_g *g);
// draw.c
void		draw_floor_ceiling(t_mlx *mlx, t_g *g);
void		draw_wall_textures(t_mlx *mlx, t_g *g);
// bonus_minimap.c
void		bonus_minimap(t_mlx *mlx, t_g *g);
// render_bonus.c
void		render_scene_with_bonus(t_mlx *mlx, t_g *g);

#endif
