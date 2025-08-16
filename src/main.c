/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleja <aleja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/16 13:23:24 by aleja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_g			*g;
	t_mlx			*mlx;

	g = NULL;
	mlx = NULL;
	if (!checks_all_errors(argc, argv, &g, &mlx))
		return (-1);
	g->mlx = mlx;
	init_player_from_map(g);
	load_textures(mlx, g);
	render_scene(mlx, g);
	setup_hooks(g);
	mlx_loop(mlx->mlx_ptr);
	destroy_window(mlx);
	free_g(g);
	return (0);
}
