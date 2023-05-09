##
## EPITECH PROJECT, 2023
## B-FUN-400-NCY-4-1-compressor-yoan.gerard
## File description:
## Makefile
##

BINARY_PATH = $(shell stack path --local-install-root)
EXE_NAME = imageCompressor-exe
NAME = imageCompressor

all:
	stack build
	cp $(BINARY_PATH)/bin/$(EXE_NAME) $(NAME)

clean:
	stack clean

fclean: clean
	rm -f $(NAME)
	rm -rf .stack-work

re: fclean all

.PHONY: all clean fclean re
