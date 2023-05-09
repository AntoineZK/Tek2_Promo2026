##
## EPITECH PROJECT, 2023
## B-NWP-400-NCY-4-1-myteams-antoine.khalidy
## File description:
## Makefile
##

NAME = graphic_client

SRC = $(shell find src/ -type f -name '*.c')

OBJ = $(SRC:.c=.o)

CSFMLFLAGS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio

CPPFLAGS = -I./include

CFLAGS = -W -Wall -Wextra -g

LDFLAGS = -L ../../libs/myteams -lmyteams -luuid

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS) $(CSFMLFLAGS)
	cp $(NAME) ../../
	rm -f $(NAME)
	make clean

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f ../../$(NAME)

re: fclean all

.PHONY: all clean fclean re
