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

// Parsea una línea del archivo .cub y actualiza la configuración (texturas o mapa)
static int parse_cub_line(t_cub_config *cfg, char *line, int *map_count, int *map_alloc) {
    if (ft_strncmp(line, "NO ", 3) == 0)
        cfg->texture_north = ft_strdup(line+3);
    else if (ft_strncmp(line, "SO ", 3) == 0)
        cfg->texture_south = ft_strdup(line+3);
    else if (ft_strncmp(line, "EA ", 3) == 0)
        cfg->texture_east = ft_strdup(line+3);
    else if (ft_strncmp(line, "WE ", 3) == 0)
        cfg->texture_west = ft_strdup(line+3);
    else if (line[0] == ' ' || line[0] == '1' || line[0] == '0') {
        if (*map_count >= *map_alloc) {
            *map_alloc *= 2;
            char **tmp = realloc(cfg->map, (*map_alloc) * sizeof(char*));
            if (!tmp) return 0;
            cfg->map = tmp;
        }
        cfg->map[(*map_count)++] = ft_strdup(line);
    }
    return 1;
}

// Lee todas las líneas del archivo .cub, las procesa y construye el mapa y la configuración
static int parse_cub_file_lines(int fd, t_cub_config *cfg) {
    char *line = NULL;
    int map_alloc = 32;
    int map_count = 0;
    cfg->map = malloc(map_alloc * sizeof(char*));
    if (!cfg->map) return 0;
    while ((line = get_next_line(fd))) {
        int len = ft_strlen(line);
        if (len > 0 && line[len-1] == '\n')
            line[len-1] = 0;
        if (!parse_cub_line(cfg, line, &map_count, &map_alloc)) {
            free(line);
            return 0;
        }
        free(line);
    }
    cfg->map_height = map_count;
    cfg->map_width = 0;
    for (int i = 0; i < map_count; i++) {
        int l = ft_strlen(cfg->map[i]);
        if (l > cfg->map_width) cfg->map_width = l;
    }
    return 1;
}

// Función principal: abre el archivo .cub, reserva memoria y llama al parser de líneas
t_cub_config *parse_cub_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0) return NULL;
    t_cub_config *cfg = ft_calloc(1, sizeof(t_cub_config));
    if (!cfg) { close(fd); return NULL; }
    if (!parse_cub_file_lines(fd, cfg)) {
        free_cub_config(cfg);
        close(fd);
        return NULL;
    }
    close(fd);
    return cfg;
}
