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

int	main(int argc, char **argv)
{
	t_cub_config	*cfg;
	t_mlx			*mlx;
	t_player		player;

	cfg = NULL;
	mlx = NULL;
	player = (t_player){0};
	if (argc != 2)
		return (printf(ERROR_ARGUMENTOS), -1);
	if (!validate_extension(argv[1]))
		return (printf(ERROR_EXTENSION), -1);
	cfg = parse_cub_file(argv[1]);
	if (!cfg)
		return (printf(ERROR_PARSEO), -1);
	if (!is_map_closed(cfg->map, cfg->map_width, cfg->map_height))
	{
		free_cub_config(cfg);
		return (printf(ERROR_MAPA_NO_CERRADO), -1);
	}
	mlx = init_window(cfg);
	if (!mlx)
	{
		free_cub_config(cfg);
		return (printf(ERROR_MLX), -1);
	}
	init_player_from_map(&player, cfg);
	render_scene(mlx, cfg, &player);
	mlx_loop(mlx->mlx_ptr);
	destroy_window(mlx);
	free_cub_config(cfg);
	return (0);
}
