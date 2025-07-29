#include "cub3d.h"

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
		write(1, buf, bytes);
	}
	close(fd);
	return (0);
}