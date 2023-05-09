##
## EPITECH PROJECT, 2023
## B-CNA-410-NCY-4-1-groundhog-yoan.gerard
## File description:
## Makefile
##

NAME = groundhog
EXEC = $(shell find -name "*.py")

all: $(NAME)

$(NAME):
	@echo "Compiling..."
	cp $(EXEC) $(NAME)

clean:
	@echo "Cleaning..."

fclean: clean
	@echo "Full cleaning..."
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
