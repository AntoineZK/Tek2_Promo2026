##
## EPITECH PROJECT, 2023
## B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
## File description:
## Makefile
##

CXX	=	g++ -std=c++17

CXXFLAGS	=	-Wall -Wextra -g

# all the source files
SRC_UPDATE_PLUGINS	=	$(wildcard ./UpdatePlugins/*.cpp)

# all the object files
OBJ_UPDATE_PLUGINS	=	$(SRC_UPDATE_PLUGINS:.cpp=.o)

# the name of the executable
NAME_UPDATE_PLUGINS	=	UpdatePlugin

# the rule to build all the executable
all:	$(NAME_UPDATE_PLUGINS)

# the rule to build the executable
$(NAME_UPDATE_PLUGINS):	$(OBJ_UPDATE_PLUGINS)
	$(CXX) -o $(NAME_UPDATE_PLUGINS) $(OBJ_UPDATE_PLUGINS) $(CXXFLAGS)

# the rule to clean the object files
clean:
	rm -f $(OBJ_UPDATE_PLUGINS)

fclean:	clean
	rm -f $(NAME_UPDATE_PLUGINS)

re:	fclean all

.PHONY:	all clean fclean re