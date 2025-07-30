#include "cub3d.h"

// Devuelve 1 si la línea es de mapa, 0 en caso contrario
static int parse_cub_line(char *line)
{
	if (line[0] == ' ' || line[0] == '1' || line[0] == '0')
		return 1;
	else
		return 0;
}

// Cuenta cuántas líneas de mapa hay en el archivo
static int count_map_lines(const char *filename)
{
	int		fd;
	char 	*line;
	int 	count = 0;
	int 	len;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return -1;
	while ((line = get_next_line(fd))) {
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = 0;
		if (parse_cub_line(line))
			count++;
		free(line);
	}
	close(fd);
	return count;
}

// Guarda las líneas de mapa en un array previamente reservado
static int fill_map_lines(const char *filename, char **lines, int count)
{
	int 	fd;
	char 	*line;
	int 	i = 0;
	int 	len;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return 0;
	while ((line = get_next_line(fd))) {
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = 0;
		if (parse_cub_line(line)) {
			if (i < count)
				lines[i++] = ft_strdup(line);
		}
		free(line);
	}
	close(fd);
	return (i == count);
}

// Orquesta el proceso de contar y guardar líneas de mapa
static int process_map_lines(const char *filename, char ***lines_out, int *count_out)
{
	int count = count_map_lines(filename);
	char **lines;
	if (count <= 0)
		return 0;
	lines = malloc(count * sizeof(char *));
	if (!lines)
		return 0;
	if (!fill_map_lines(filename, lines, count)) {
		int i = 0;
		while (i < count) {
			free(lines[i]);
			i++;
		}
		free(lines);
		return 0;
	}
	*lines_out = lines;
	*count_out = count;
	return 1;
}

// Crea el mapa en cfg a partir de las líneas procesadas
static int create_map(t_cub_config *cfg, char **lines, int count)
{
	int l;
	cfg->map = malloc(count * sizeof(char *));
	if (!cfg->map)
		return 0;
	cfg->map_height = count;
	cfg->map_width = 0;
	int i = 0;
	while (i < count)
	{
		cfg->map[i] = ft_strdup(lines[i]);
		l = ft_strlen(lines[i]);
		if (l > cfg->map_width)
			cfg->map_width = l;
		i++;
	}
	return 1;
}


// Lee todas las líneas del archivo .cub, las procesa y construye el mapa y la configuración
static int parse_cub_file_lines(const char *filename, t_cub_config *cfg)
{
	char 	**lines = NULL;
	int 	count = 0;
	if (!process_map_lines(filename, &lines, &count))
		return 0;
	if (!create_map(cfg, lines, count))
	{
		int i = 0;
		while (i < count) {
			free(lines[i]);
			i++;
		}
		free(lines);
		return 0;
	}
	{
		int i = 0;
		while (i < count) {
			free(lines[i]);
			i++;
		}
	}
	free(lines);
	return 1;
}

// Función principal: abre el archivo .cub, reserva memoria y llama al parser de líneas
t_cub_config	*parse_cub_file(const char *filename)
{
	int				fd;
	t_cub_config	*cfg;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	cfg = ft_calloc(1, sizeof(t_cub_config));
	if (!cfg)
	{
		close(fd);
		return (NULL);
	}
	if (!parse_cub_file_lines(filename, cfg))
	{
		free_cub_config(cfg);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (cfg);
}
