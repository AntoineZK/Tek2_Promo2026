##
## EPITECH PROJECT, 2023
## B-YEP-400-NCY-4-1-zappy-antoine.khalidy
## File description:
## Makefile
##

# SOURCE AND OBJECTS #
SRC = $(shell find source/ -type f -name '*.c')
SRC_SERV = $(shell find ../../server/source/ -type f -name '*.c' ! -name 'main.c')
OBJ = $(SRC:.c=.o)
OBJ_SERVER = $(SRC_SERV:.c=.o)

# NAME #
NAME = unit_tests

# FLAGS #
CPPFLAGS = -Iinclude/
CFLAGS = -Wall -Wextra -W -g -lm -lncurses

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_SERVER)
	make -C ../../server
	gcc -o $(NAME) $(OBJ) $(OBJ_SERVER) $(CFLAGS) --coverage -lcriterion
	mv $(NAME) ../../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../../$(NAME)

re: fclean all

.PHONY: all clean fclean re
