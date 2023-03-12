/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** comp4011
*/

#pragma once
#include "../AGate.hpp"

namespace nts {
    class comp4011 : public AGate {
        public:
            comp4011(int nbPin = 14);
            ~comp4011() = default;
            nts::Tristate compute(std::size_t pin);
    };
}