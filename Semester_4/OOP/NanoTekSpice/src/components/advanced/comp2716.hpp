/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** comp2716
*/

#pragma once
#include "../AAdvanced.hpp"

namespace nts {
    class comp2716 : public AAdvanced {
        public:
            comp2716(int nbPin = 16);
            ~comp2716() = default;
            nts::Tristate compute(std::size_t pin);
    };
}
