##
## EPITECH PROJECT, 2023
## B-OOP-400-NCY-4-1-arcade-antoine.khalidy
## File description:
## Makefile
##

# Names
NAME = arcade
NAME_SFML = arcade_sfml.so
NAME_SDL2 = arcade_sdl2.so
NAME_NCURSES = arcade_ncurses.so
NAME_SNAKE = arcade_snake.so
NAME_PACMAN = arcade_pacman.so
NAME_MENU = arcade_menu.so
NAME_SFMLAUDIO = arcade_sfmlaudio.so
NAME_SDL2AUDIO = arcade_sdl2audio.so
NAME_RAYLIB = arcade_raylib.so

# Sources
SRC_CORE = $(wildcard sources/Core/*.cpp)
SRC_SFML = $(wildcard sources/Graphics/SFML/*.cpp)
SRC_SDL2 = $(wildcard sources/Graphics/SDL2/*.cpp)
SRC_NCURSES = $(wildcard sources/Graphics/NCurses/*.cpp)
SRC_SNAKE = $(wildcard sources/Game/Snake/*.cpp)
SRC_PACMAN = $(wildcard sources/Game/Pacman/*.cpp)
SRC_MENU = $(wildcard sources/Game/Menu/*.cpp)
SRC_SFMLAUDIO = $(wildcard sources/Audio/SFMLAudio/*.cpp)
SRC_SDL2AUDIO = $(wildcard sources/Audio/SDL2Audio/*.cpp)
SRC_RAYLIB = $(wildcard sources/Graphics/Raylib/*.cpp)

# Objects
OBJ_CORE = $(SRC_CORE:.cpp=.o)
OBJ_SFML = $(SRC_SFML:.cpp=.o)
OBJ_SDL2 = $(SRC_SDL2:.cpp=.o)
OBJ_NCURSES = $(SRC_NCURSES:.cpp=.o)
OBJ_SNAKE = $(SRC_SNAKE:.cpp=.o)
OBJ_PACMAN = $(SRC_PACMAN:.cpp=.o)
OBJ_MENU = $(SRC_MENU:.cpp=.o)
OBJ_SFMLAUDIO = $(SRC_SFMLAUDIO:.cpp=.o)
OBJ_SDL2AUDIO = $(SRC_SDL2AUDIO:.cpp=.o)
OBJ_RAYLIB = $(SRC_RAYLIB:.cpp=.o)

# Flags
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SDL2FLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image
NCURSESFLAGS = -lncurses
SFMLAUDIOFLAGS = -lsfml-audio
SDL2AUDIOFLAGS = -lSDL2_mixer
RAYLIBFLAGS = -lraylib
CXXFLAGS += -W -Wall -Wextra -std=c++17 -g -fPIC -fno-gnu-unique
CXX = g++

# Rules
all: core graphicals games audio

core: $(OBJ_CORE)
	$(CXX) -o $(NAME) $(OBJ_CORE) -ldl -rdynamic -export-dynamic

games: $(OBJ_SNAKE) $(OBJ_PACMAN) $(OBJ_MENU)
	mkdir -p lib
	$(CXX) -shared -o lib/$(NAME_MENU) $(OBJ_MENU)
	$(CXX) -shared -o lib/$(NAME_SNAKE) $(OBJ_SNAKE)
	$(CXX) -shared -o lib/$(NAME_PACMAN) $(OBJ_PACMAN)

graphicals: $(OBJ_SFML) $(OBJ_SDL2) $(OBJ_NCURSES) $(OBJ_RAYLIB)
	mkdir -p lib
	$(CXX) -shared -o lib/$(NAME_SFML) $(OBJ_SFML) $(SFMLFLAGS)
	$(CXX) -shared -o lib/$(NAME_SDL2) $(OBJ_SDL2) $(SDL2FLAGS)
	$(CXX) -shared -o lib/$(NAME_NCURSES) $(OBJ_NCURSES) $(NCURSESFLAGS)
	$(CXX) -shared -o lib/$(NAME_RAYLIB) $(OBJ_RAYLIB) $(RAYLIBFLAGS)

audio: $(OBJ_SFMLAUDIO) $(OBJ_SDL2AUDIO)
	$(CXX) -shared -o lib/$(NAME_SFMLAUDIO) $(OBJ_SFMLAUDIO) $(SFMLAUDIOFLAGS)
	$(CXX) -shared -o lib/$(NAME_SDL2AUDIO) $(OBJ_SDL2AUDIO) $(SDL2AUDIOFLAGS)

clean:
	rm -f $(OBJ_CORE) $(OBJ_SFML) $(OBJ_SDL2) $(OBJ_NCURSES) $(OBJ_SNAKE) $(OBJ_PACMAN) $(OBJ_MENU) $(OBJ_SFMLAUDIO) $(OBJ_SDL2AUDIO) $(OBJ_RAYLIB)

fclean: clean
	rm -rf $(NAME) lib

re: fclean all lib

.PHONY: all clean fclean re
