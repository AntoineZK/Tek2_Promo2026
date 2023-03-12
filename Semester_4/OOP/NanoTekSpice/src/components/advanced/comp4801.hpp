/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** comp4801
*/

#pragma once
#include "../AAdvanced.hpp"

namespace nts {
    class comp4801 : public AAdvanced {
        public:
            comp4801(int nbPin = 16);
            ~comp4801() = default;
            nts::Tristate compute(std::size_t pin);
    };
}
