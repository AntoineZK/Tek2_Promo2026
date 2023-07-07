/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** main
*/

#include "Core/Core.hpp"

int main(int ac, char **av)
{
    RT::Raytracer raytracer;

    std::cout << "Raytracer is running" << std::endl;

    try {
        raytracer.errorHandling(ac, av);
        raytracer.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}