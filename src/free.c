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

void free_cub_config(t_cub_config *cfg)
{
    if (!cfg) return;
    free(cfg->texture_north);
    free(cfg->texture_south);
    free(cfg->texture_east);
    free(cfg->texture_west);

    if (cfg->map) {
        for (int i = 0; i < cfg->map_height; i++)
            free(cfg->map[i]);
        free(cfg->map);
    }
    free(cfg);
}
