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

int main(int argc, char **argv)
{
    if (argc != 2)
        return (printf(ERROR_ARGUMENTOS), -1);
    if (!validate_extension(argv[1]))
        return (printf(ERROR_EXTENSION), -1);

    t_cub_config *cfg = parse_cub_file(argv[1]);
    if (!cfg)
        return (printf(ERROR_PARSEO), -1);

    t_mlx *mlx = init_window(cfg);
    if (!mlx) {
        free_cub_config(cfg);
        return (printf(ERROR_MLX), -1);
    }
    mlx_loop(mlx->mlx_ptr);
    destroy_window(mlx);
    free_cub_config(cfg);
    return (0);
}