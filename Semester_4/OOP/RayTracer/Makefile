##
## EPITECH PROJECT, 2023
## B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
## File description:
## Makefile
##

# NAMES
NAME = raytracer

# SOURCES
SRC = $(shell find ./MainRaytracer -not -path "./MainRaytracer/RayTracing/*" -name "*.cpp")
SRC += $(shell find ./Libs/Loader -name "*.cpp")
SRC += $(shell find ./Libs/Network -name "*.cpp")
SRC += $(shell find ./ExternClient -name "*.cpp" ! -name "main.cpp")

# OBJECTS
OBJ = $(SRC:.cpp=.o)

# FLAGS
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CXXFLAGS += -W -Wall -Wextra -std=c++17 -g
CXX = g++ -o2

# RULES
all: client $(NAME)

client:
	make -C ExternClient

$(NAME): $(OBJ)
	@echo "\033[1;33mCompilation of $(NAME)\033[0m"
	$(CXX) -o $(NAME) $(OBJ) -lpthread -lconfig++ $(SFML_FLAGS)
	@echo "\033[1;32mCompilation successfull\033[0m"

#insertion point

clean_rt:
	@echo "\033[1;31mCleaning\033[0m"
	rm -f $(OBJ)
	@echo "\033[1;31mCleaned\033[0m"

clean_client:
	make -C ExternClient clean

clean: clean clean_client

fclean_rt: clean_rt
	@echo "\033[1;31mFull Cleaning\033[0m"
	rm -f $(NAME)
	@echo "\033[1;31mFull Cleaned\033[0m"

fclean_client:
	make -C ExternClient fclean

fclean: fclean_rt fclean_client

re: fclean all

.PHONY: all clean fclean re
