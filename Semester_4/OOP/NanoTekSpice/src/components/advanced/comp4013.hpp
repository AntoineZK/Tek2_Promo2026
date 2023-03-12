/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** comp4013
*/

#pragma once
#include "../AAdvanced.hpp"

namespace nts {
    class comp4013 : public AAdvanced {
        public:
            comp4013(int nbPin = 16);
            ~comp4013() = default;
            nts::Tristate compute(std::size_t pin);
    };
}
