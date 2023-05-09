/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** main
*/

#include "Core.hpp"
#include "DLLoader.hpp"

int main(int ac, char **av)
{
    arcade::Core arcade;

    if (ac != 2)
        return arcade.helper(84);
    try {
        arcade.loadLibs();
        arcade.runGame(av[1]);
    } catch (arcade::Core::CoreException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (arcade::DLLoader::DLLoaderException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
