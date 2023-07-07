/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-bsraytracer-antoine.khalidy
** File description:
** Include
*/

#pragma once
    #include "../../../MainRaytracer/Include/Include.hpp"


const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

namespace RT {
    namespace Random {
        namespace Utils {
            double degrees_to_radians(double degrees);
            double random_double();
            double random_double(double min, double max);
            int random_int(int min, int max);
        }
    }
}