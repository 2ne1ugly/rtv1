# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 15:18:59 by mchi              #+#    #+#              #
#    Updated: 2019/04/02 21:04:05 by mchi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc

SRCDIR=./src/

SRC=img.c init.c intersect.c key.c loop.c matrix.c rtv1.c shoot_rays.c \
vector.c vector2.c world_view_proj.c

SRCALL=$(addprefix $(SRCDIR), $(SRC))

LIB=-lmlx -lm -lft -L./libft -L./minilibx_macos -framework OpenGL -framework AppKit
INC=-Iinclude -Ilibft -Iminilibx_macos
FLAG=-Wall -Werror -Wextra -Ofast

LIBFT=./libft/libft.a

MINILIBX=./minilibx_macos/libmlx.a
 
OBJ=img.o init.o intersect.o key.o loop.o matrix.o rtv1.o shoot_rays.o \
vector.o vector2.o world_view_proj.o

NAME=RTv1

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX)
	$(CC) $(FLAG) -c $(INC) $(SRCALL)
	$(CC) $(FLAG) $(LIB) $(INC) $(OBJ) -o $(NAME)

$(LIBFT):
	make -C libft

$(MINILIBX):
	make -C minilibx_macos

clean:
#	make -C libft clean
#	make -C minilibx_macos clean
	rm -rf $(OBJ)

fclean: clean
#	rm -f $(MINILIBX)
#	rm -f $(LIBFT)
	rm -f $(NAME)

re:
	make fclean
	make all