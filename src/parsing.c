#include "cub3d.h"

int	validate_extension(const char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len < 4)
		return (0);
	return (filename[len - 4] == '.' && filename[len - 3] == 'c' && filename[len - 2] == 'u' && filename[len - 1] == 'b');
}

int	open_cub_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	return (fd);
}

int	read_cub_file(const char *filename)
{
	int		fd;
	char	buf[1025];
	int		bytes;

	fd = open_cub_file(filename);
	if (fd < 0)
		return (1);
	while ((bytes = read(fd, buf, 1024)) > 0)
	{
		buf[bytes] = '\0';
		write(1, buf, bytes); // Solo imprime el contenido
	}
	close(fd);
	return (0);
}