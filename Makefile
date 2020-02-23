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
		readmap

SRCS = $(patsubst %, %.c, $(CFILES))

OUT = $(patsubst %, %.o, $(CFILES))

INCL = ./

FLAGS = -Werror -Wall -Wextra

LIB = ./lib

all: $(NAME)

%.o:%.c -I$(INCL)
	@$(CC) $(FLAGS) $(INCL) $< -o $@

$(NAME):
	@make -C $(LIB)
	@$(CC) $(FLAGS) -o $(NAME) $(SRCS) -I $(INCL) -L. lib/libft.a

clean:
	@rm -f $(OUT)
	@make -C $(LIB) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB) fclean

re: fclean all

.PHONY: all clean fclean re
