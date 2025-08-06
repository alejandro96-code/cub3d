/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/06 10:47:53 by ybahri           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub_config	*cfg;
	t_mlx			*mlx;
	t_player		player;
	t_game			game;

	cfg = NULL;
	mlx = NULL;
	player = (t_player){0};
	if (!checksAllErrors(argc, argv, &cfg, &mlx))
		return (-1);
	init_player_from_map(&player, cfg);
	game.mlx = mlx;
	game.cfg = cfg;
	game.player = &player;
	render_scene(mlx, cfg, &player);
	setup_hooks(&game);
	mlx_loop(mlx->mlx_ptr);
	//destroy_window(mlx);
	//free_cub_config(cfg);
	return (0);
}
