##
## EPITECH PROJECT, 2023
## B-YEP-400-NCY-4-1-zappy-antoine.khalidy
## File description:
## Makefile
##

# SOURCE AND OBJECTS #
SRC = $(shell find source/ -type f -name '*.c')
OBJ = $(SRC:.c=.o)

# NAME #
NAME = zappy_server

# FLAGS #
CPPFLAGS = -Iinclude/
CFLAGS = -Wall -Wextra -W -g -lm -lncurses

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)
	mv $(NAME) ../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
