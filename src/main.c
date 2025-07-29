#include "cub3d.h"

int	main(int argc, char **argv)
{
    if (argc != 2)
        return (write (1, "Error\nNº de argumentos invalido\n", 34), -1);
    else if (argv[1][0] == '\0')
        return (write (1, "Error\nArgumento vacio\n", 23), -1);
    if (!validate_extension(argv[1]))
		return (write (1, "Error\nExtension de archivo invalida\n", 36), -1);
	read_cub_file(argv[1]);
    printf("iniciando el juego...\n");
	return (0);
}
