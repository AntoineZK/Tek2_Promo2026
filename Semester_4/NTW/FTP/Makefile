##
## EPITECH PROJECT, 2023
## B-NWP-400-NCY-4-1-myftp-antoine.khalidy
## File description:
## Makefile
##

SRC = $(shell find src/ -type f -name '*.c')

OBJ = $(SRC:.c=.o)

NAME = myftp

CPPFLAGS = -I./include

CFLAGS = -Wall -Wextra -Wno-unused-parameter -Wno-unused-function \
		 -Wno-unused-variable -g

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
