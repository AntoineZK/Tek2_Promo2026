/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** comp4094
*/

#pragma once
#include "../AAdvanced.hpp"

namespace nts {
    class comp4094 : public AAdvanced {
        public:
            comp4094(int nbPin = 16);
            ~comp4094() = default;
            nts::Tristate compute(std::size_t pin);
    };
}
