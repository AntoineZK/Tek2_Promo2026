/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** comp4008
*/

#pragma once
#include "../AAdvanced.hpp"

namespace nts {
    class comp4008 : public AAdvanced {
        public:
            comp4008(int nbPin = 16);
            ~comp4008() = default;
            nts::Tristate compute(std::size_t pin);
    };
}
