/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Light
*/

#pragma once
#include "../IObjParser.hpp"

namespace RT {
    namespace Parsing {
        class Light {
            public:
                Light();
                void create(libconfig::Setting& cfg);
                std::string getName() const;
                ~Light();

            protected:
            private:
                std::vector<double> _point_pos;
                std::vector<double> _point_color;
                std::vector<double> _direct_direct;
                std::vector<double> _direct_color;

        };
    };
};
