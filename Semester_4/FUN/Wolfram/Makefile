##
## EPITECH PROJECT, 2023
## B-FUN-400-NCY-4-1-wolfram-antoine.khalidy
## File description:
## Makefile
##

BINARY_PATH = $(shell stack path --local-install-root)
EXE_NAME = wolfram-exe
NAME = wolfram

all:
	stack build
	cp $(BINARY_PATH)/bin/$(EXE_NAME) .
	mv $(EXE_NAME) $(NAME)

clean:
	stack clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
