/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** comp4030
*/

#pragma once
#include "../AGate.hpp"

namespace nts {
    class comp4030 : public AGate {
        public:
            comp4030(int nbPin = 14);
            ~comp4030() = default;
            nts::Tristate compute(std::size_t pin);
    };
}