##
## EPITECH PROJECT, 2023
## B-ASM-400-NCY-4-1-asmminilibc-antoine.khalidy
## File description:
## Makefile
##

# export LD_LIBRARY_PATH=$PWD

NAME = libasm.so

SRC_ASM = $(wildcard ./src/asm_lib/*.asm)

SRC = ./src/main.c

OBJ = $(SRC_ASM:.asm=.o)

all: $(NAME)

$(NAME):
	$(foreach file, $(SRC_ASM), nasm -f elf64 $(file);)
	ld -shared -o $(NAME) $(OBJ) -fPIC -Bsymbolic

test: all
	gcc -o test $(SRC) -L. -lasm

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f test

re: fclean all

.PHONY: all clean fclean re
