/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:27:21 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/26 01:20:46 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_g		*g;
	t_mlx	*mlx;

	g = NULL;
	mlx = NULL;
	checks_all_errors(argc, argv, &g, &mlx);
	g->mlx = mlx;
	init_player_from_map(g);
	load_textures(mlx, g);
	render_scene_with_bonus(mlx, g);
	setup_hooks(g);
	mlx_loop(mlx->mlx_ptr);
	destroy_window(mlx);
	free_g(g);
	return (0);
}
