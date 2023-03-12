/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** comp4514
*/

#pragma once
#include "../AAdvanced.hpp"

namespace nts {
    class comp4514 : public AAdvanced {
        public:
            comp4514(int nbPin = 16);
            ~comp4514() = default;
            nts::Tristate compute(std::size_t pin);
    };
}
