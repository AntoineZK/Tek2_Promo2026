/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** 4001
*/

#pragma once
#include "../AGate.hpp"

namespace nts {
    class comp4001 : public AGate {
        public:
            comp4001(int nbPin = 14);
            ~comp4001() = default;
            nts::Tristate compute(std::size_t pin);
    };
}