CC=clang
CFLAGS=-Werror -Wextra -Wall -g -Ilibft -I. -Imlx -Iinclude -Ofast
LFLAGS=-L libft/ -lft -L mlx/ -lmlx -framework OpenGL -framework AppKit
SRC=$(wildcard src/*)
NAME=RTv1
OBJ=$(SRC:src/%.c=%.o)
SHELL := /bin/bash

.PHONY: clean fclean all re norm norme debug test norman update libft

VPATH = src obj libft/includes include

$(NAME): $(OBJ)
	@make -C mlx
	@make -C libft
	@$(CC) -o $(NAME) obj/* $(LFLAGS)
	@echo "RTv1 build complete!"

all: $(NAME)

%.o: %.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -o obj/$@ -c $<

clean:
	@make -C mlx clean
	@make -C libft/ clean
	@rm -rf obj/

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)

re: fclean all

norm:
	norminette src/. includes/.

norme: norm

norman:
	-norminette * | grep -iv warning
