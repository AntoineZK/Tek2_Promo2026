/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** comp4017
*/

#pragma once
#include "../AAdvanced.hpp"

namespace nts {
    class comp4017 : public AAdvanced {
        public:
            comp4017(int nbPin = 16);
            ~comp4017() = default;
            nts::Tristate compute(std::size_t pin);
    };
}
