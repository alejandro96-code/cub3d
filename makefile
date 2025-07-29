NAME = cub3d
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

SRC =	src/main.c \
		src/parsing.c \
		src/checks_errors.c \
                
OBJS = $(SRC:.c=.o)

UNAME_S := $(shell uname -s)

MLXFLAGS = -L mlx -lmlx -lX11 -lXext -lbsd -lm

all: $(NAME)

%.o: %.c
	@$(CC) -I src/ $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJS)	
	@printf "\e[43m\e[30mCompilando Archivos Propios\e[0m\n"
	@printf "\e[42m\e[30mArchivos Propios Compilados\e[0m\n"

	@printf "\e[43m\e[30mCompilando MLX\e[0m\n"
	@$(MAKE) -C mlx 2>/dev/null >/dev/null
	@printf "\e[42m\e[30mArchivos MLX Compilada\e[0m\n"

	@printf "\e[43m\e[30mPreparando la librería MLX\e[0m\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) mlx/libmlx.a $(MLXFLAGS)
	@printf "\e[42m\e[30mListo para jugar!\e[0m\n"

clean:
	@make clean -C mlx
	@printf "\e[42m\e[30mEliminados los archivos generados de MLX .o\e[0m\n"
	@rm -f $(OBJS)
	@printf "\e[42m\e[30mEliminados los archivos generados propios .o\e[0m\n"


fclean: clean
	rm -f $(NAME)
	@printf "\e[42m\e[30mEliminados todos los archivos generados\e[0m\n"

re: fclean all

.PHONY: all clean fclean re
