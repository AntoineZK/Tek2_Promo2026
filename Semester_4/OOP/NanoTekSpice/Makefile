##
## EPITECH PROJECT, 2023
## B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
## File description:
## Makefile
##

SRC = $(shell find ./src/ -type f -name '*.cpp')

OBJ = $(SRC:.cpp=.o)

NAME = nanotekspice

CPPFLAGS += -Wall -Wextra -I./include -std=c++17 -g -Wno-unused-variable -Wno-unused-parameter

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
