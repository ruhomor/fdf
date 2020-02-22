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
