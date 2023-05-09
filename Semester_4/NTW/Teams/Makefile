##
## EPITECH PROJECT, 2023
## B-NWP-400-NCY-4-1-myteams-antoine.khalidy
## File description:
## Makefile
##

all: core

core:
	make -s -C client_part
	make -s -C server_part

clean:
	make -s -C client_part clean
	make -s -C server_part clean

bonus:
	make re -s -C bonus/graphical

fclean: clean
	make -s -C client_part fclean
	make -s -C server_part fclean
	make -s -C bonus/graphical fclean

clean_bonus:
	make -s -C bonus fclean

re: fclean all

.PHONY: all clean fclean re bonus clean_bonus
