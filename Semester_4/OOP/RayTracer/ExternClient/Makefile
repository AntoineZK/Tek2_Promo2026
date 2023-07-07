##
## EPITECH PROJECT, 2023
## B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
## File description:
## Makefile
##

CXXFLAGS += -W -Wall -Wextra -std=c++17 -g -I/usr/include/libconfig

CXX = g++ -o2

NAME_EXTERN_CLIENT = RTexternClient

SRC_EXTERN_CLIENT = $(shell find ../Libs/Network -name "*.cpp")
SRC_EXTERN_CLIENT += $(shell find ./src -name "*.cpp")
SRC_EXTERN_CLIENT += $(shell find ../Libs/Loader -name "*.cpp")
SRC_EXTERN_CLIENT += $(shell find ../MainRaytracer/Include/ -name "*.cpp")
SRC_EXTERN_CLIENT += $(shell find ../MainRaytracer/Core/Utils -name "*.cpp")

OBJ_EXTERN_CLIENT = $(SRC_EXTERN_CLIENT:.cpp=.o)

all: $(NAME_EXTERN_CLIENT)

$(NAME_EXTERN_CLIENT): $(OBJ_EXTERN_CLIENT)
	@echo $(SRC_EXTERN_CLIENT)
	@echo "\033[1;33mCompilation of $(NAME_EXTERN_CLIENT)\033[0m"
	$(CXX) -o $(NAME_EXTERN_CLIENT) $(OBJ_EXTERN_CLIENT) -lpthread -lconfig++
	@echo "\033[1;32mCompilation successfull\033[0m"
	mv $(NAME_EXTERN_CLIENT) ../

clean:
	@echo "\033[1;31mCleaning client\033[0m"
	rm -f $(OBJ_EXTERN_CLIENT)
	@echo "\033[1;31mCleaned\033[0m"

fclean: clean
	@echo "\033[1;31mFull Cleaning client\033[0m"
	rm -f ../$(NAME_EXTERN_CLIENT)
	@echo "\033[1;31mFull Cleaned\033[0m"

re: fclean all

.PHONY: all clean fclean re
