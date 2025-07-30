
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