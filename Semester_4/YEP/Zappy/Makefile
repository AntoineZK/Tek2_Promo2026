##
## EPITECH PROJECT, 2023
## B-YEP-400-NCY-4-1-zappy-antoine.khalidy
## File description:
## Makefile
##

all:
	@echo "\033[1;33mCompiling server...\033[0m"
	@make -C server
	@echo "\033[1;33mCompiling gui...\033[0m"
	@make -C gui
	@echo "\033[1;33mCompiling tests...\033[0m"
	@make -C tests
	@echo "\033[1;32mCompiling Done !\033[0m"

clean:
	@echo "\033[1;33mCleaning server...\033[0m"
	@make clean -C server
	@echo "\033[1;33mCleaning gui...\033[0m"
	@make clean -C gui
	@echo "\033[1;33mCleaning tests...\033[0m"
	@make clean -C tests
	@echo "\033[1;32mCleaning Done !\033[0m"

fclean:
	@echo "\033[1;33mFull Cleaning server...\033[0m"
	@make fclean -C server
	@echo "\033[1;33mFull Cleaning gui...\033[0m"
	@make fclean -C gui
	@echo "\033[1;33mFull Cleaning tests...\033[0m"
	@make fclean -C tests
	@echo "\033[1;32mFull Cleaning Done !\033[0m"

re:
	@echo "\033[1;33mRecompiling server...\033[0m"
	@make re -C server
	@echo "\033[1;33mRecompiling gui...\033[0m"
	@make re -C gui
	@echo "\033[1;33mRecompiling tests...\033[0m"
	@make re -C tests
	@echo "\033[1;32mRecompiling Done !\033[0m"

.PHONY: all clean fclean re
