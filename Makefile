# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kachiote <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/23 22:57:04 by kachiote          #+#    #+#              #
#    Updated: 2020/02/23 22:57:06 by kachiote         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = fdf

CFILES = fdf \
		readmap \
		readmap2 \
		linecolornew \
		line1 \
		line2 \
		line3 \
		line4 \
		line5 \
		line6 \
		support1 \
		support2 \
		support3 \
		support4 \
		support5 \
		support6

FW = -framework OpenGL -framework AppKit

SRCS = $(patsubst %, %.c, $(CFILES))

OUT = $(patsubst %, %.o, $(CFILES))

INCL = lib/libft.a minilibx_macos/libmlx.a

FLAGS = -Werror -Wall -Wextra -g

LIB = ./lib

GLIB = ./minilibx_macos

all: $(NAME)

%.o:%.c -I./
	@$(CC) $(FLAGS) $(INCL) $< -o $@

$(NAME):
	@make -C $(LIB)
	@make -C $(GLIB)
	@$(CC) $(FLAGS) -o $(NAME) $(SRCS) $(INCL) $(FW)

clean:
	@rm -f $(OUT)
	@make -C $(GLIB) clean
	@make -C $(LIB) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB) fclean

re: fclean all

.PHONY: all clean fclean re
