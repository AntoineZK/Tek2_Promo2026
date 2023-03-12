/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** comp4040
*/

#pragma once
#include "../AAdvanced.hpp"

namespace nts {
    class comp4040 : public AAdvanced {
        public:
            comp4040(int nbPin = 16);
            ~comp4040() = default;
            nts::Tristate compute(std::size_t pin);
            void simulate(std::size_t tick = 0);
        private:
            size_t _tick = 0;
    };
}
