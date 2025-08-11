/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/11 19:41:54 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub_config	*cfg;
	t_mlx			*mlx;
	t_player		player;
	t_hook_data		hook_data;

	cfg = NULL;
	mlx = NULL;
	player = (t_player){0};
	if (!checks_all_errors(argc, argv, &cfg, &mlx))
		return (-1);
	init_player_from_map(&player, cfg);
	load_textures(mlx, cfg);
	render_scene(mlx, cfg, &player);
	setup_hooks(mlx, cfg, &player, &hook_data);
	mlx_loop(mlx->mlx_ptr);
	destroy_window(mlx);
	free_cub_config(cfg);
	return (0);
}
