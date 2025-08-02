NAME = cub3d
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f


# Archivos de la libft
LIBFTSRC = \
	src/libft/ft_isalpha.c \
	src/libft/ft_isdigit.c \
	src/libft/ft_isalnum.c \
	src/libft/ft_isascii.c \
	src/libft/ft_isprint.c \
	src/libft/ft_strlen.c \
	src/libft/ft_memset.c \
	src/libft/ft_bzero.c \
	src/libft/ft_memcpy.c \
	src/libft/ft_memmove.c \
	src/libft/ft_strlcpy.c \
	src/libft/ft_strlcat.c \
	src/libft/ft_toupper.c \
	src/libft/ft_tolower.c \
	src/libft/ft_strchr.c \
	src/libft/ft_strrchr.c \
	src/libft/ft_strncmp.c \
	src/libft/ft_memchr.c \
	src/libft/ft_memcmp.c \
	src/libft/ft_strnstr.c \
	src/libft/ft_atoi.c \
	src/libft/ft_strdup.c \
	src/libft/ft_calloc.c \
	src/libft/ft_substr.c \
	src/libft/ft_strjoin.c \
	src/libft/ft_strtrim.c \
	src/libft/ft_split.c \
	src/libft/ft_itoa.c \
	src/libft/ft_strmapi.c \
	src/libft/ft_striteri.c \
	src/libft/ft_putchar_fd.c \
	src/libft/ft_putstr_fd.c \
	src/libft/ft_putendl_fd.c \
	src/libft/ft_putnbr_fd.c

# Archivos de get_next_line
GNLSRC = \
	src/gnl/get_next_line.c \
	src/gnl/get_next_line_utils.c

# Archivos principales del proyecto

CUB3DSRC = \
   src/main.c \
   src/checks_errors.c \
   src/init_window.c \
   src/parsing.c \
   src/renderScene.c \
   src/free.c \
   src/init_player.c \
   src/drawColors.c \
   src/raycast_calc.c \
   src/bonus_minimap.c

# Directorio de objetos
OBJDIR = src/obj

# Objetos en el directorio obj
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(CUB3DSRC:.c=.o))) \
       $(addprefix $(OBJDIR)/, $(notdir $(LIBFTSRC:.c=.o))) \
       $(addprefix $(OBJDIR)/, $(notdir $(GNLSRC:.c=.o)))

UNAME_S := $(shell uname -s)

MLXFLAGS = -L mlx -lmlx -lX11 -lXext -lbsd -lm

all: $(NAME)

# Crear directorio obj si no existe
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Reglas para compilar archivos .c a .o en el directorio obj
$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@$(CC) -I src/ $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: src/libft/%.c | $(OBJDIR)
	@$(CC) -I src/ $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: src/gnl/%.c | $(OBJDIR)
	@$(CC) -I src/ $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)	
	@printf "\e[43m\e[30mCompilando Archivos Propios\e[0m\n"
	@printf "\e[42m\e[30mArchivos Propios Compilados\e[0m\n"

	@printf "\e[43m\e[30mCompilando MLX\e[0m\n"
	@$(MAKE) -C mlx 2>/dev/null >/dev/null
	@printf "\e[42m\e[30mArchivos MLX Compilada\e[0m\n"

	@printf "\e[43m\e[30mPreparando el cub3d\e[0m\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) mlx/libmlx.a $(MLXFLAGS)
	@printf "\e[42m\e[30mListo para jugar!\e[0m\n"

clean:
	@make clean -C mlx 2>/dev/null >/dev/null
	@printf "\e[41m\e[30mEliminados los archivos generados de MLX .o\e[0m\n"
	@rm -rf $(OBJDIR)
	@printf "\e[41m\e[30mEliminados los archivos generados propios .o y carpeta obj\e[0m\n"


fclean: clean
	@rm -f $(NAME)
	@printf "\e[41m\e[30mEliminados todos los archivos generados\e[0m\n"

re: fclean all

.PHONY: all clean fclean re

