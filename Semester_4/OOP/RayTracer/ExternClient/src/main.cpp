/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** main
*/

#include "Core/Core.hpp"

int main(void)
{
   RT::Core core;
   try {
      core.initConnection();
      core.run();
   } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
   }
   std::cerr << "\nDone.\n";
   return (0);
}
