#include "cub3d.h"

// Dibuja un cuadrado en el minimapa
static void draw_square(void *mlx_ptr, void *win_ptr, int x, int y, int color)
{
    int i, j;
    for (i = 0; i < MINIMAP_CELL_SIZE; i++)
        for (j = 0; j < MINIMAP_CELL_SIZE; j++)
            mlx_pixel_put(mlx_ptr, win_ptr, x + i, y + j, color);
}

// Renderiza un minimapa fijo en la esquina superior izquierda
void bonus_minimap(t_mlx *mlx, t_cub_config *cfg)
{
    int y, x;
    for (y = 0; y < cfg->map_height; y++)
    {
        for (x = 0; x < cfg->map_width; x++)
        {
            int px = MINIMAP_MARGIN + x * MINIMAP_CELL_SIZE;
            int py = MINIMAP_MARGIN + y * MINIMAP_CELL_SIZE;
            char c = cfg->map[y][x];
            if (c == '1')
                draw_square(mlx->mlx_ptr, mlx->win_ptr, px, py, MINIMAP_WALL_COLOR);
            else if (c == '0')
                draw_square(mlx->mlx_ptr, mlx->win_ptr, px, py, MINIMAP_FLOOR_COLOR);
            else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                draw_square(mlx->mlx_ptr, mlx->win_ptr, px, py, MINIMAP_PLAYER_COLOR);
        }
    }
}
