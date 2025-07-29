
#include "cub3d.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        return (printf(ERROR_ARGUMENTOS), -1);
    if (!validate_extension(argv[1]))
        return (printf(ERROR_EXTENSION), -1);
    read_cub_file(argv[1]);
    printf("iniciando el juego...\n");
    return (0);
}
